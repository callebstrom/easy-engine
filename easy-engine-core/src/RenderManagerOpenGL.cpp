#include <EasyEngine/eepch.h>

#include <GL/glew.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glfw3.h>

#include <boost/lexical_cast.hpp>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <EasyEngine/render_manager/ObjectIndex.h>
#include <EasyEngine/render_manager/RenderManagerOpenGL.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/render_manager/_3DObjectRenderable.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/ecs/component/TextureComponent.h>
#include <EasyEngine/ecs/component/MaterialComponent.h>
#include <EasyEngine/shader_manager/ShaderManagerOpenGL.h>
#include <EasyEngine/shader_manager/Shader.h>
#include <EasyEngine/resource/Environment.h>
#include <EasyEngine/Logger.h>

void GLAPIENTRY Debug(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam) {
	// EE_CORE_TRACE(message​);
	// EE_CORE_TRACE("hello");
	std::cout << "hello";
};

namespace easy_engine {

	using shader_manager::ShaderManagerOpenGL;

	namespace render_manager {
		typedef configuration::RenderConfigurationParams c_params_;

		constexpr GLint LIGHTS_BINDING_POINT = 0;
		constexpr ushort_t NO_OF_VEC3_IN_POINT_LIGHT = 4;
		constexpr ushort_t NO_OF_VEC3_IN_DIRECTIONAL_LIGHT = 4;
		constexpr ushort_t MAX_POINT_LIGHTS = 128;
		constexpr ushort_t MAX_DIRECTIONAL_LIGHTS = 4;
		constexpr size_t VEC3_SIZE_WITH_PADDING = sizeof(GLfloat) * 4;

		static GLint MAX_TEXTURE_IMAGE_UNITS = 0;

		struct RenderManagerOpenGL::Impl {

			Impl(configuration::RenderConfiguration_t* rc, std::shared_ptr<ShaderManagerOpenGL> shader_manager)
				: render_config_(rc), camera(new Camera), shader_manager(shader_manager) {
				glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_IMAGE_UNITS);
			}

			void LogRenderInfo() const;

			void CreateDefaultPipeline() {

				auto vertex_shader = this->shader_manager->LoadShaderByPath(this->render_config_->Get(c_params_::VERTEX_SHADER_SOURCE_LOCATION), shader_manager::ShaderType::kVertex);
				auto pixel_shader = this->shader_manager->LoadShaderByPath(this->render_config_->Get(c_params_::FRAGMENT_SHADER_SOURCE_LOCATION), shader_manager::ShaderType::kPixel);

				if (!vertex_shader) {
					EE_CORE_ERROR("Could not load default vertex shader");
					return;
				}

				if (!pixel_shader) {
					EE_CORE_ERROR("Could not load default pixel shader");
					return;
				}

				auto shader_pipeline = this->shader_manager->CreateShaderPipeline();

				this->shader_manager->AttachShader(vertex_shader, shader_pipeline);
				this->shader_manager->AttachShader(pixel_shader, shader_pipeline);

				this->shader_manager->LinkPipeline(shader_pipeline);
			}

			void LogRenderInfo() {
				EE_CORE_INFO("Renderer: {}", std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER)))));
				EE_CORE_INFO("OpenGL version supported: {}", std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))));
			}

			void InitializeTexture(const resource::Material& material, resource::Texture& texture, int texture_image_unit) {
				if (texture.renderer_id == 0) {

					glActiveTexture(texture_image_unit);

					GLuint renderer_id;
					glGenTextures(1, &renderer_id);

					glBindTexture(GL_TEXTURE_2D, renderer_id);

					int format = 0;

					if (texture.bpp == 3) format = GL_RGB;
					else if (texture.bpp == 4) format = GL_RGBA;
					else EE_CORE_WARN("Unknown texture bpp");

					glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, texture.raw);
					glGenerateMipmap(GL_TEXTURE_2D);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

					texture.renderer_id = renderer_id;
					texture.Free();
				}
			}

			void GenerateObjectIndex(resource::Renderable* renderable_, std::vector<resource::Texture*> textures, std::optional<resource::Material*> maybe_material) {
				if (glGenVertexArrays == NULL) {
					EE_CORE_CRITICAL("glGenVertexArrays is not supported");
					throw new std::runtime_error("glGenVertexArrays is not supported");
				}

				{
					const void* address = static_cast<const void*>(glGenVertexArrays);
					std::stringstream ss;
					ss << address;
					std::string glGenVertexArraysAddr = ss.str();
					EE_CORE_TRACE("glGenVertexArrays [" + glGenVertexArraysAddr + "]");
				}

				resource::Mesh* renderable = static_cast<resource::Mesh*>(renderable_);
				ObjectIndex object_index;

				glGenVertexArrays(1, &object_index.vao);
				EE_CORE_TRACE("Generated vertex array object for " + renderable->name);

				// Set active VAO
				glBindVertexArray(object_index.vao);

				GLuint vbo, ebo, texture_coord_buffer, normal_buffer;

				glGenBuffers(1, &vbo);
				EE_CORE_TRACE("Generated vertex buffer object for " + renderable->name);

				glGenBuffers(1, &normal_buffer);
				EE_CORE_TRACE("Generated normal buffer object for " + renderable->name);

				glGenBuffers(1, &ebo);
				EE_CORE_TRACE("Generated element array for " + renderable->name);

				glGenBuffers(1, &texture_coord_buffer);

				// Set active VBO to position VBO
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glEnableVertexAttribArray(0);

				// VERTEX BUFFER
				glBufferData(
					GL_ARRAY_BUFFER,
					renderable->vertices.size() * sizeof(GLfloat),
					renderable->vertices.data(),
					GL_STATIC_DRAW
				);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				// !VERTEX BUFFER

				// UV BUFFER
				glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
				glEnableVertexAttribArray(1);
				glBufferData(
					GL_ARRAY_BUFFER,
					renderable->texture_coords.size() * sizeof(GLfloat),
					renderable->texture_coords.data(),
					GL_STATIC_DRAW
				);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
				// !UV BUFFER

				// NORMAL BUFFER
				glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
				glEnableVertexAttribArray(2);
				glBufferData(
					GL_ARRAY_BUFFER,
					renderable->vertex_normals.size() * sizeof(GLfloat),
					renderable->vertex_normals.data(),
					GL_STATIC_DRAW
				);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				// !NORMAL BUFFER

				// Create an element array
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(
					GL_ELEMENT_ARRAY_BUFFER,
					renderable->faces.size() * sizeof(GLuint),
					&renderable->faces[0],
					GL_STATIC_DRAW
				);

				if (maybe_material.has_value()) {
					auto material = maybe_material.value();
					if (textures.size() >= material->diffuse_texture_index) {
						resource::Texture* diffuse_texture = textures[material->diffuse_texture_index];

						this->InitializeTexture(*material, *diffuse_texture, GL_TEXTURE0);
					}

					if (textures.size() >= material->emissive_texture_index) {
						resource::Texture* emissive_texture = textures[material->emissive_texture_index];

						this->InitializeTexture(*material, *emissive_texture, GL_TEXTURE1);
					}
				}

				// Unbind VAO
				glBindVertexArray(0);

				// VBO and EBO can be deleted as VAO hold a reference to these
				glDeleteBuffers(1, &vbo);
				glDeleteBuffers(1, &ebo);
				glDeleteBuffers(1, &texture_coord_buffer);

				object_index.ebo_size = renderable->faces.size();

				this->object_indices_.insert(std::pair<std::string, ObjectIndex>(renderable->name, object_index));
			};

			auto InterpolateTranslation3f(Eigen::Translation3f prev, Eigen::Translation3f cur) const -> std::vector<Eigen::Translation3f> {
				static float MIN_LERP_STEP = 0.001f;
				float x_diff = prev.x() - cur.x();
				float y_diff = prev.y() - cur.y();
				float z_diff = prev.z() - cur.z();

				return std::vector<Eigen::Translation3f>();
			}

			void On3DObjectRenderable(event_manager::Event event) {
				_3DObjectRenderable* event_data = static_cast<_3DObjectRenderable*>(event.data);

				Eigen::Matrix<GLfloat, 4, 4> identity_matrix;
				identity_matrix.setZero();
				identity_matrix.diagonal() << 1, 1, 1, 1;

				auto prev_translation = event_data->transform_component->GetPreviousTranslation();
				auto translation = event_data->transform_component->GetTranslation();

				auto combined_affine_transform = event_data->transform_component->GetTranslation() * event_data->transform_component->GetRotation() * event_data->transform_component->GetScale();
				Eigen::Matrix<GLfloat, 4, 4> model_matrix = combined_affine_transform * identity_matrix;

				this->SetupGlobalState();

				for (auto mesh : *event_data->mesh_component->sub_meshes) {
					auto material = event_data->material_component.has_value() && event_data->material_component.value()->materials->size() - 1 >= mesh->material_index
						? std::optional<resource::Material*>(event_data->material_component.value()->materials->at(mesh->material_index))
						: std::nullopt;

					auto textures = event_data->texture_component.has_value()
						? *event_data->texture_component.value()->textures
						: std::vector<resource::Texture*>();

					this->Render(
						mesh,
						model_matrix,
						textures,
						material
					);
				}
			}

			auto BindTexture(const resource::Texture& texture, const resource::Material& material, int texture_image_unit) const -> void {
				if (texture_image_unit <= MAX_TEXTURE_IMAGE_UNITS) EE_CORE_WARN("Available texture units exhausted");
				glActiveTexture(texture_image_unit);
				glBindTexture(GL_TEXTURE_2D, texture.renderer_id);
			}

			auto SetupGlobalState() -> void {
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glEnable(GL_BLEND);

				glEnable(GL_CULL_FACE);

				glViewport(
					0,
					0,
					atoi(this->render_config_->Get(c_params_::RESOLUTION_X).c_str()),
					atoi(this->render_config_->Get(c_params_::RESOLUTION_Y).c_str())
				);

				glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

				glUseProgram(this->shader_manager->GetAttachedPipeline()->GetId());
			}

			auto Render(resource::Mesh* mesh, Eigen::Matrix4f model_matrix_, std::vector<resource::Texture*> textures, std::optional<resource::Material*> maybe_material) -> void {

				// Should the object index be built lazily?
				if (this->object_indices_.find(mesh->name) == this->object_indices_.end()) {
					this->GenerateObjectIndex(mesh, textures, maybe_material);
				}

				ObjectIndex object_index = this->object_indices_.at(mesh->name);

				bool has_diffuse_texture = false;
				bool has_emissive_texture = false;

				// TODO split into new function BindMaterial
				if (maybe_material.has_value()) {
					auto material = maybe_material.value();

					if (textures.size() > material->diffuse_texture_index) {
						this->BindTexture(*textures[material->diffuse_texture_index], *material, GL_TEXTURE0);
						has_diffuse_texture = true;
					}

					if (textures.size() > material->emissive_texture_index) {
						this->BindTexture(*textures[material->emissive_texture_index], *material, GL_TEXTURE1);
						has_emissive_texture = true;
					}

					GLint materialDiffuseColor = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "materialDiffuseColor");
					auto diffuse_color = material->diffuse_color;
					glUniform3f(materialDiffuseColor, diffuse_color.x(), diffuse_color.y(), diffuse_color.z());

					GLint hasDiffuseTexture = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "hasDiffuseTexture");
					glUniform1f(hasDiffuseTexture, has_diffuse_texture ? 1 : 0);

					GLint materialSpecularColor = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "materialSpecularColor");
					auto specular_color = material->specular_color;
					glUniform3f(materialSpecularColor, specular_color.x(), specular_color.y(), specular_color.z());

					GLint materialShininess = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "materialShininess");
					auto shininess = material->shininess;
					glUniform1f(materialShininess, shininess);

					GLint materialEmmisiveColor = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "materialEmmisiveColor");
					auto emmisive_color = material->emmisive_color;
					glUniform3f(materialEmmisiveColor, emmisive_color.x(), emmisive_color.y(), emmisive_color.z());

					GLint hasEmissiveTexture = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "hasEmissiveTexture");
					glUniform1f(hasEmissiveTexture, has_emissive_texture ? 1 : 0);
				}

				float FoV = 70.0f;

				auto width = boost::lexical_cast<float>(this->render_config_->Get(c_params_::RESOLUTION_X));
				auto height = boost::lexical_cast<float>(this->render_config_->Get(c_params_::RESOLUTION_Y));
				GLfloat aspect_ratio = width / height;

				glm::mat4 projection_matrix = glm::perspective(
					glm::radians(FoV),
					aspect_ratio,
					0.1f,
					100.0f
				);

				auto view_matrix = this->camera->view_matrix;
				auto model_matrix = glm::make_mat4(model_matrix_.data());

				glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

				GLint mvp_uniform = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "mvp");
				glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp));

				GLint model_uniform = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "model");
				glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model_matrix));

				GLint view_uniform = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "view");
				glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view_matrix));

				GLint cameraPosition_worldspace = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "cameraPosition_worldspace");
				glUniform3fv(cameraPosition_worldspace, 1, &this->camera->position[0]);

				glBindVertexArray(object_index.vao);
				glShadeModel(GL_SMOOTH);
				glDrawElements(GL_TRIANGLES, object_index.ebo_size, GL_UNSIGNED_INT, NULL);
			}

			void OnPreRender() {
				this->RenderLights();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void OnPostRender() {

			}

			int GetPointLightOffsetInBytes(int offset) {
				static const std::vector<size_t> point_light_size_vector ={
					VEC3_SIZE_WITH_PADDING,
					sizeof(float),
					sizeof(float),
					sizeof(float),
					VEC3_SIZE_WITH_PADDING,
					VEC3_SIZE_WITH_PADDING,
					VEC3_SIZE_WITH_PADDING,
					sizeof(float)
				};

				return std::accumulate(point_light_size_vector.begin(), std::next(point_light_size_vector.begin(), offset), 0);
			}

			int GetDirectionalLightOffsetInBytes(int offset) {
				static const std::vector<size_t> directional_light_size_vector ={
					VEC3_SIZE_WITH_PADDING,
					VEC3_SIZE_WITH_PADDING,
					VEC3_SIZE_WITH_PADDING,
					VEC3_SIZE_WITH_PADDING,
					sizeof(float)
				};

				return std::accumulate(directional_light_size_vector.begin(), std::next(directional_light_size_vector.begin(), offset), 0);
			}

			void RenderLights() {

				unsigned int lights_uniform_block_index = glGetUniformBlockIndex(this->shader_manager->GetAttachedPipeline()->GetId(), "Lights");
				glUniformBlockBinding(this->shader_manager->GetAttachedPipeline()->GetId(), lights_uniform_block_index, LIGHTS_BINDING_POINT);

				unsigned int lights_ubo;
				glGenBuffers(1, &lights_ubo);

				const auto point_light_padding = sizeof(float) * NO_OF_VEC3_IN_POINT_LIGHT; // One float of padding per vec3 as these are stored as vec4 in GLSL
				const auto directional_light_padding = sizeof(float) * NO_OF_VEC3_IN_DIRECTIONAL_LIGHT; // One float of padding per vec3 as these are stored as vec4 in GLSL

				const auto point_light_size = sizeof(resource::PointLight) + point_light_padding;
				const auto directional_light_size = sizeof(resource::DirectionalLight) + directional_light_padding;

				const auto lights_size = (point_light_size * MAX_POINT_LIGHTS) + (directional_light_size * MAX_DIRECTIONAL_LIGHTS);

				glBindBuffer(GL_UNIFORM_BUFFER, lights_ubo);
				glBufferData(GL_UNIFORM_BUFFER, lights_size, NULL, GL_STATIC_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);

				glBindBufferRange(GL_UNIFORM_BUFFER, 0, lights_ubo, 0, lights_size);

				glBindBuffer(GL_UNIFORM_BUFFER, lights_ubo);

				GLint point_light_count_uniform = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "point_light_count");
				glUniform1f(point_light_count_uniform, this->point_lights_with_translations.size());

				GLint directional_light_count_uniform = glGetUniformLocation(this->shader_manager->GetAttachedPipeline()->GetId(), "directional_light_count");
				glUniform1f(directional_light_count_uniform, this->directional_lights_with_translations.size());

				// Point lights
				for (int i = 0; i < this->point_lights_with_translations.size(); i++) {
					auto light = this->point_lights_with_translations[i].first;
					auto translation = this->point_lights_with_translations[i].second;

					auto point_light_offset = i * point_light_size;

					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset, VEC3_SIZE_WITH_PADDING, translation.data());
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(1), sizeof(float), &light.constant);
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(2), sizeof(float), &light.linear);
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(3), sizeof(float), &light.quadratic);
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(4), VEC3_SIZE_WITH_PADDING, light.ambient_color.data());
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(5), VEC3_SIZE_WITH_PADDING, light.diffuse_color.data());
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(6), VEC3_SIZE_WITH_PADDING, light.specular_color.data());
					glBufferSubData(GL_UNIFORM_BUFFER, point_light_offset + this->GetPointLightOffsetInBytes(7), sizeof(float), &light.strength);
				}

				// Directional lights
				for (int i = 0; i < this->directional_lights_with_translations.size(); i++) {
					auto light =  this->directional_lights_with_translations[i].first;

					auto directional_light_offset = i * directional_light_size + (MAX_POINT_LIGHTS * point_light_size);
					glBufferSubData(GL_UNIFORM_BUFFER, directional_light_offset, VEC3_SIZE_WITH_PADDING, light.direction.data());
					glBufferSubData(GL_UNIFORM_BUFFER, directional_light_offset + this->GetDirectionalLightOffsetInBytes(1), VEC3_SIZE_WITH_PADDING, light.ambient_color.data());
					glBufferSubData(GL_UNIFORM_BUFFER, directional_light_offset + this->GetDirectionalLightOffsetInBytes(2), VEC3_SIZE_WITH_PADDING, light.diffuse_color.data());
					glBufferSubData(GL_UNIFORM_BUFFER, directional_light_offset + this->GetDirectionalLightOffsetInBytes(3), VEC3_SIZE_WITH_PADDING, light.specular_color.data());
					glBufferSubData(GL_UNIFORM_BUFFER, directional_light_offset + this->GetDirectionalLightOffsetInBytes(4), sizeof(float), &light.strength);
				}

				glBindBuffer(GL_UNIFORM_BUFFER, 0);

				this->point_lights_with_translations.clear();
				this->directional_lights_with_translations.clear();
			}

			configuration::RenderConfiguration_t* render_config_;
			std::vector<resource::Renderable*> render_queue;

			float last_time_;

			glm::mat4 mvp = glm::mat4(1.0);
			std::map<std::string, ObjectIndex> object_indices_;
			std::vector<GLfloat> vertex_buffer_data_;
			GLuint vertex_shader_;
			GLuint fragment_shader_;
			GLuint shader_program_;
			GLint pos_attrib_;
			GLint uniform_attrib_;
			GLint col_attrib_;
			Camera* camera;
			float factor = 1.0f;

			GLint diffuse_texture_sampler;
			GLint emissive_texture_sampler;

			std::vector<std::pair<resource::PointLight, Eigen::Vector3f>> point_lights_with_translations;
			std::vector<std::pair<resource::DirectionalLight, Eigen::Vector3f>> directional_lights_with_translations;

			std::shared_ptr<ShaderManagerOpenGL> shader_manager;
		};

		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration_t* rc, std::shared_ptr<ShaderManagerOpenGL> shader_manager)
			: p_impl_(new Impl(rc, shader_manager)) {

			glewExperimental = GL_TRUE;
			GLenum glew_error = glewInit();

			if (glew_error != GLEW_OK) {
				EE_CORE_CRITICAL("Failed to init GLEW: " + boost::lexical_cast<std::string>(glewGetErrorString(glew_error)));
			}

			this->p_impl_->CreateDefaultPipeline();

			ManagerLocator::event_manager->Subscribe(
				event_manager::EventType::kPreRender,
				this
			);

			ManagerLocator::event_manager->Subscribe(
				event_manager::EventType::kPostRender,
				this
			);

			ManagerLocator::event_manager->Subscribe(
				event_manager::EventType::k3DObjectRenderable,
				this
			);

			this->p_impl_->LogRenderInfo();
		};

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glDeleteProgram(this->p_impl_->shader_program_);
			glDeleteShader(this->p_impl_->fragment_shader_);
			glDeleteShader(this->p_impl_->vertex_shader_);
		}

		void RenderManagerOpenGL::Render(resource::Mesh* mesh, Eigen::Matrix4f model_matrix, std::vector<resource::Texture*> textures, resource::Material* material) {
			this->p_impl_->Render(mesh, model_matrix, textures, material);
		}

		void RenderManagerOpenGL::Render(resource::PointLight point_light, Eigen::Vector3f translation) {
			auto light_translation_pair = std::make_pair(point_light, translation);
			this->p_impl_->point_lights_with_translations.push_back(light_translation_pair);
		}
		
		void RenderManagerOpenGL::Render(resource::DirectionalLight directional_light, Eigen::Vector3f translation) {
			auto light_translation_pair = std::make_pair(directional_light, translation);
			this->p_impl_->directional_lights_with_translations.push_back(light_translation_pair);
		}

		void RenderManagerOpenGL::OnEvent(event_manager::Event event) {
			switch (event.event_type) {
			case event_manager::EventType::k3DObjectRenderable:
				this->p_impl_->On3DObjectRenderable(event);
				break;
			case event_manager::EventType::kPreRender:
				this->p_impl_->OnPreRender();
				break;
			case event_manager::EventType::kPostRender:
				this->p_impl_->OnPostRender();
				break;
			}
		}

		// TODO this should be handled by WindowManager using glfwSetWindowUserPointer
		void RenderManagerOpenGL::UpdateCameraAngle(double x, double y) {

			static double lastTime = glfwGetTime();
			double currentTime = glfwGetTime();
			float deltaTime = float(currentTime - lastTime);

			// position
			glm::vec3 position = glm::vec3(0, 0, 20);

			// horizontal angle : toward -Z
			float horizontalAngle = 3.14f;

			// vertical angle : 0, look at the horizon
			float verticalAngle = 0.0f;

			static const float mouseSpeed = 0.1f;

			horizontalAngle += mouseSpeed * deltaTime * float(boost::lexical_cast<int>(this->p_impl_->render_config_->Get(configuration::RenderConfigurationParams::RESOLUTION_X)) / 2 - x);
			verticalAngle += mouseSpeed * deltaTime * float(boost::lexical_cast<int>(this->p_impl_->render_config_->Get(configuration::RenderConfigurationParams::RESOLUTION_Y)) / 2 - y);

			glm::vec3 direction = glm::vec3(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
			);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - 3.14f / 2.0f),
				0,
				cos(horizontalAngle - 3.14f / 2.0f)
			);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			float FoV = 45.0f;

			static glm::mat4 projection_matrix = glm::perspective(glm::radians(FoV), 16.0f / 9.0f, 0.1f, 100.0f);

			glm::mat4 view_matrix;

			// Camera matrix
			view_matrix = glm::lookAt(
				position,				// Camera is here
				position + direction,	// and looks here : at the same position, plus "direction"
				up						// Head is up (set to 0,-1,0 to look upside-down)
			);

			glm::mat4 model_matrix = glm::mat4(1.0);
			this->p_impl_->mvp = projection_matrix * view_matrix * glm::scale(model_matrix, glm::vec3(1, 1, 1));
			lastTime = lastTime + deltaTime;
		}

		void RenderManagerOpenGL::SetShaderPipeline(Ref<shader_manager::ShaderPipeline> shader_pipeline) {
			this->p_impl_->shader_program_ = shader_pipeline->GetId();
		}
	}
}