﻿#include <EasyEngine/eepch.h>

#include <GL/glew.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glfw3.h>

#include <boost/lexical_cast.hpp>

#include <EasyEngine/render_manager/ObjectIndex.h>
#include <EasyEngine/render_manager/RenderManagerOpenGL.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/render_manager/Camera.h>
#include <EasyEngine/render_manager/_3DObjectRenderable.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/ecs/component/TextureComponent.h>
#include <EasyEngine/ecs/component/MaterialComponent.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>

void GLAPIENTRY Debug(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam) {
	// EE_CORE_TRACE(message​);
	// EE_CORE_TRACE("hello");
	std::cout << "hello";
};

namespace easy_engine {
	namespace render_manager {
		typedef configuration::RenderConfigurationParams c_params_;

		struct RenderManagerOpenGL::Light {
			glm::vec3 position;
			glm::vec3 intensities; //a.k.a. the color of the light
		};

		struct RenderManagerOpenGL::Impl {

			Impl(configuration::RenderConfiguration_t* rc)
				: render_config_(rc), camera(new Camera) {}

			void LogRenderInfo() const;
			void LoadShaders() {
				std::ifstream vertex_in(this->render_config_->Get(c_params_::VERTEX_SHADER_SOURCE_LOCATION));
				std::string vertex_contents((std::istreambuf_iterator<char>(vertex_in)),
					std::istreambuf_iterator<char>());

				std::ifstream fragment_in(this->render_config_->Get(c_params_::FRAGMENT_SHADER_SOURCE_LOCATION));
				std::string fragment_contents((std::istreambuf_iterator<char>(fragment_in)),
					std::istreambuf_iterator<char>());

				const char* vertex_source = vertex_contents.c_str();
				const char* fragment_source = fragment_contents.c_str();

				if (vertex_source == "")
					throw std::runtime_error("Empty vertex shader source");
				else if (fragment_source == "")
					throw std::runtime_error("Empty fragment shader source");

				this->vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(this->vertex_shader_, 1, &vertex_source, NULL);
				glCompileShader(this->vertex_shader_);

				this->fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(this->fragment_shader_, 1, &fragment_source, NULL);
				glCompileShader(this->fragment_shader_);

				GLint vertex_status, fragment_status;
				glGetShaderiv(this->vertex_shader_, GL_COMPILE_STATUS, &vertex_status);
				glGetShaderiv(this->fragment_shader_, GL_COMPILE_STATUS, &fragment_status);

				char shader_log_buffer[512];

				if (vertex_status != GL_TRUE) {
					const std::string message = "Could not compile vertex shader: ";
					glGetShaderInfoLog(this->vertex_shader_, 256, NULL, shader_log_buffer);
					EE_CORE_CRITICAL(message + shader_log_buffer);
				}
				else if (fragment_status != GL_TRUE) {
					const std::string message = "Could not compile fragment shader: ";
					glGetShaderInfoLog(this->fragment_shader_, 256, NULL, shader_log_buffer);
					EE_CORE_CRITICAL(message + shader_log_buffer);
				}

				this->shader_program_ = glCreateProgram();
				glAttachShader(this->shader_program_, this->vertex_shader_);
				glAttachShader(this->shader_program_, this->fragment_shader_);

				glBindFragDataLocation(this->shader_program_, 1, "outColor");

				glLinkProgram(this->shader_program_);
				glUseProgram(this->shader_program_);
			};

			void LogRenderInfo() {
				EE_CORE_INFO("Renderer: {}", std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER)))));
				EE_CORE_INFO("OpenGL version supported: {}", std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))));
			}

			void GenerateObjectIndex(resource::Renderable * renderable_, std::vector<resource::Texture*> textures, resource::Material * material) {
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

				if (textures.size() >= material->diffuse_texture_index) {
					resource::Texture* diffuse_texture = textures[material->diffuse_texture_index];

					if (diffuse_texture != nullptr && diffuse_texture->renderer_id == 0) {

						glActiveTexture(GL_TEXTURE0);

						GLuint renderer_id;
						glGenTextures(1, &renderer_id);


						glBindTexture(GL_TEXTURE_2D, renderer_id);

						int format = 0;

						if (diffuse_texture->bpp == 3) format = GL_RGB;
						else if (diffuse_texture->bpp == 4) format = GL_RGBA;
						else EE_CORE_WARN("Unknown texture bpp");

						glTexImage2D(GL_TEXTURE_2D, 0, format, diffuse_texture->width, diffuse_texture->height, 0, format, GL_UNSIGNED_BYTE, diffuse_texture->raw);
						glGenerateMipmap(GL_TEXTURE_2D);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						diffuse_texture->renderer_id = renderer_id;
					}
				}

				if (textures.size() >= material->emissive_texture_index) {
					resource::Texture* emissive_texture = textures[material->emissive_texture_index];

					if (emissive_texture != nullptr && emissive_texture->renderer_id == 0) {

						glActiveTexture(GL_TEXTURE1);

						GLuint renderer_id;
						glGenTextures(1, &renderer_id);


						glBindTexture(GL_TEXTURE_2D, renderer_id);

						int format = 0;

						if (emissive_texture->bpp == 3) format = GL_RGB;
						else if (emissive_texture->bpp == 4) format = GL_RGBA;
						else EE_CORE_WARN("Unknown texture bpp");

						glTexImage2D(GL_TEXTURE_2D, 0, format, emissive_texture->width, emissive_texture->height, 0, format, GL_UNSIGNED_BYTE, emissive_texture->raw);
						glGenerateMipmap(GL_TEXTURE_2D);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						emissive_texture->renderer_id = renderer_id;
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

			std::vector<Eigen::Translation3f> InterpolateTranslation3f(Eigen::Translation3f prev, Eigen::Translation3f cur) {
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

				auto prev_translation = event_data->transform_component->prev_translation_;
				auto translation = event_data->transform_component->translation_;

				// TODO interpolate between the 2 translations above and render for interpolation step for;
				for (auto translation_interpolation_step : this->InterpolateTranslation3f(prev_translation, translation))
				{

				}

				auto combined_affine_transform = event_data->transform_component->translation_ * event_data->transform_component->rotation * event_data->transform_component->scale;
				Eigen::Matrix<GLfloat, 4, 4> model_matrix = combined_affine_transform * identity_matrix;

				for (auto mesh : *event_data->mesh_component->sub_meshes) {

					auto material = event_data->material_component != nullptr && event_data->has_materials && event_data->material_component->materials->size() - 1 >= mesh->material_index
						? event_data->material_component->materials->at(mesh->material_index)
						: nullptr;

					if (material == nullptr) {
						auto zz = "";
					}

					this->Render(mesh, model_matrix, *event_data->texture_component->textures, material);
				}
			}

			void Render(resource::Mesh * mesh, Eigen::Matrix4f model_matrix_, std::vector<resource::Texture*> textures, resource::Material * material) {
				// Should the object index be built lazily?
				if (this->object_indices_.find(mesh->name) == this->object_indices_.end()) {
					this->GenerateObjectIndex(mesh, textures, material);
				}

				ObjectIndex object_index = this->object_indices_.at(mesh->name);

				bool has_diffuse_texture = false;
				bool has_emissive_texture = false;

				if (textures.size() >= material->diffuse_texture_index) {
					resource::Texture* diffuse_texture = textures[material->diffuse_texture_index];

					if (diffuse_texture != nullptr) {
						glBindTexture(GL_TEXTURE_2D, diffuse_texture->renderer_id);
						has_diffuse_texture = true;
					}
				}

				if (textures.size() >= material->emissive_texture_index) {
					resource::Texture* emissive_texture = textures[material->emissive_texture_index];

					if (emissive_texture != nullptr) {
						glBindTexture(GL_TEXTURE_2D, emissive_texture->renderer_id);
						has_emissive_texture = true;
					}
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

				// Pre-compute matrices for the shaders
				GLint mvp_uniform = glGetUniformLocation(this->shader_program_, "mvp");
				glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp));

				// Model matrix is required separately to calculate lightning
				GLint model_uniform = glGetUniformLocation(this->shader_program_, "model");
				glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model_matrix));

				// View matrix is required separately to calculate lightning
				GLint view_uniform = glGetUniformLocation(this->shader_program_, "view");
				glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view_matrix));

				glm::vec3 light_position(this->camera->position); // Same as camera for now
				glm::vec3 light_color(1.f, 1.f, 1.f);

				GLint lightPower = glGetUniformLocation(this->shader_program_, "lightPower");
				glUniform1f(lightPower, 1000.f);

				GLint lightPosition_worldspace = glGetUniformLocation(this->shader_program_, "lightPosition_worldspace");
				glUniform3fv(lightPosition_worldspace, 1, &light_position[0]);

				GLint lightColor = glGetUniformLocation(this->shader_program_, "lightColor");
				glUniform3fv(lightColor, 1, &light_color[0]);

				GLint cameraPosition_worldspace = glGetUniformLocation(this->shader_program_, "cameraPosition_worldspace");
				glUniform3fv(cameraPosition_worldspace, 1, &this->camera->position[0]);

				// TODO split into separate function RenderMaterial
				if (material != nullptr) {
					GLint materialDiffuseColor = glGetUniformLocation(this->shader_program_, "materialDiffuseColor");
					auto diffuse_color = material->diffuse_color;
					glUniform3f(materialDiffuseColor, diffuse_color.x(), diffuse_color.y(), diffuse_color.z());

					GLint hasDiffuseTexture = glGetUniformLocation(this->shader_program_, "hasDiffuseTexture");
					glUniform1f(hasDiffuseTexture, has_diffuse_texture ? 1 : 0);

					GLint materialSpecularColor = glGetUniformLocation(this->shader_program_, "materialSpecularColor");
					auto specular_color = material->specular_color;
					glUniform3f(materialSpecularColor, specular_color.x(), specular_color.y(), specular_color.z());

					GLint materialShininess = glGetUniformLocation(this->shader_program_, "materialShininess");
					auto shininess = material->shininess;
					glUniform1f(materialShininess, shininess);

					GLint hasEmissiveTexture = glGetUniformLocation(this->shader_program_, "hasEmissiveTexture");
					glUniform1f(hasEmissiveTexture, has_emissive_texture ? 1 : 0);
				}

				glBindVertexArray(object_index.vao);
				glShadeModel(GL_SMOOTH);
				glDrawElements(GL_TRIANGLES, object_index.ebo_size, GL_UNSIGNED_INT, NULL);
			}

			void OnPreRender() {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		};

		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration_t * rc)
			: p_impl_(new Impl(rc)) {

			glewExperimental = GL_TRUE;
			GLenum glew_error = glewInit();

			if (glew_error != GLEW_OK) {
				EE_CORE_CRITICAL("Failed to init GLEW: " + boost::lexical_cast<std::string>(glewGetErrorString(glew_error)));
			}

			glEnable(GL_DEPTH_TEST); // enable depth-testing
			glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

			this->p_impl_->LoadShaders();

			// Set background to dark grey
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// Draw to the entire window
			glViewport(
				0,
				0,
				atoi(this->p_impl_->render_config_->Get(c_params_::RESOLUTION_X).c_str()),
				atoi(this->p_impl_->render_config_->Get(c_params_::RESOLUTION_Y).c_str())
			);

			// Don't render triangles with normal facing away from camera
			glEnable(GL_CULL_FACE);
			// glDebugMessageCallback(&Debug, nullptr);

			ManagerLocator::event_manager->Subscribe(
				event_manager::EventType::_3DPreRender,
				this
			);

			ManagerLocator::event_manager->Subscribe(
				event_manager::EventType::_3DObjectRenderable,
				this
			);

			this->p_impl_->LogRenderInfo();
		};

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glDeleteProgram(this->p_impl_->shader_program_);
			glDeleteShader(this->p_impl_->fragment_shader_);
			glDeleteShader(this->p_impl_->vertex_shader_);
		}

		void RenderManagerOpenGL::Render(resource::Mesh * mesh, Eigen::Matrix4f model_matrix, std::vector<resource::Texture*> textures, resource::Material * material) {
			this->p_impl_->Render(mesh, model_matrix, textures, material);
		}

		void RenderManagerOpenGL::OnEvent(event_manager::Event event) {
			switch (event.event_type) {
			case event_manager::EventType::_3DObjectRenderable:
				this->p_impl_->On3DObjectRenderable(event);
				break;
			case event_manager::EventType::_3DPreRender:
				this->p_impl_->OnPreRender();
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
	}
}