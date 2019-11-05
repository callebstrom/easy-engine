#include <EasyEngine/eepch.h>

#include <GL/glew.h>
#include <GL/GLU.h>

#include <EasyEngine/Logger.h>
#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/shader_manager/ShaderManagerOpenGL.h>
#include <EasyEngine/shader_manager/Shader.h>

namespace easy_engine {
	namespace shader_manager {

		struct ShaderManagerOpenGL::Impl {
			Impl() {}

			auto CompileShader(Ref<Shader> shader) const -> std::optional<GLuint> {
				auto internal_type = this->internal_type_map.at(shader->type);
				GLuint shader_descriptor = glCreateShader(internal_type);
				auto source = shader->GetSource();
				glShaderSource(shader_descriptor, 1, &source, NULL);
				glCompileShader(shader_descriptor);

				GLint compile_status;
				glGetShaderiv(shader_descriptor, GL_COMPILE_STATUS, &compile_status);

				if (compile_status != GL_TRUE) {
					char shader_log_buffer[512];
					const std::string message = "Could not compile " + this->shader_type_name.at(shader->type) + " shader";
					glGetShaderInfoLog(compile_status, 256, NULL, shader_log_buffer);
					EE_CORE_CRITICAL(message + shader_log_buffer);
					return std::nullopt;
				}

				return std::make_optional(shader_descriptor);
			}

			const std::map<ShaderType, int> internal_type_map ={
				{ ShaderType::kVertex, GL_VERTEX_SHADER },
				{ ShaderType::kPixel, GL_FRAGMENT_SHADER },
				{ ShaderType::kGeometry, GL_GEOMETRY_SHADER }
			};
			const std::map<ShaderType, std::string> shader_type_name ={
				{ ShaderType::kVertex, "vertex" },
				{ ShaderType::kPixel, "pixel" },
				{ ShaderType::kGeometry, "geometry" }
			};
			std::vector<std::shared_ptr<Shader>> shaders;
		};

		ShaderManagerOpenGL::ShaderManagerOpenGL()
			: p_impl_(new Impl()) {}

		ShaderManagerOpenGL::~ShaderManagerOpenGL() {}

		auto ShaderManagerOpenGL::LoadShader(std::string path, ShaderType type) -> std::shared_ptr<Shader> {

			auto shader_source = resource_manager::ResourceManager::LoadFileAsString(path);
			auto shader = CreateRef<Shader>(this->p_impl_->shaders.size(), shader_source, type);

			auto maybe_internal_id = this->p_impl_->CompileShader(shader);

			if (maybe_internal_id.has_value()) {
				shader->id = maybe_internal_id.value();
				this->p_impl_->shaders.push_back(std::move(shader));
				return this->p_impl_->shaders.back();
			}

			return nullptr;
		}

		auto ShaderManagerOpenGL::AttachPipeline(Ref<ShaderPipeline> pipeline) -> void {
			glUseProgram(pipeline->GetId());
		}

		auto ShaderManagerOpenGL::AttachShader(Ref<Shader> shader, Ref<ShaderPipeline> pipeline) -> void {
			glAttachShader(pipeline->GetId(), shader->id);
			pipeline->AddShader(shader);
		}

		auto ShaderManagerOpenGL::CreateShaderPipeline() -> Ref<ShaderPipeline> {
			return CreateRef<ShaderPipeline>(glCreateProgram());
		}

		void ShaderManagerOpenGL::LinkPipeline(Ref<ShaderPipeline> pipeline) {
			// glBindFragDataLocation(pipeline->GetId(), 1, "outColor");
			glLinkProgram(pipeline->GetId());

			auto pixel_shader = pipeline->GetPixelShader();

			if (!pixel_shader) {
				EE_CORE_ERROR("Cannot link pipeline: no pixel shader attached");
			}

			pixel_shader->diffuse_texture_sampler = glGetUniformLocation(pipeline->GetId(), "diffuseTextureSampler2D");
			pixel_shader->emissive_texture_sampler = glGetUniformLocation(pipeline->GetId(), "emissiveTextureSampler2D");

			this->AttachPipeline(pipeline);

			glUniform1i(pixel_shader->diffuse_texture_sampler, 0);
			glUniform1i(pixel_shader->emissive_texture_sampler, 1);
		}

	}
}