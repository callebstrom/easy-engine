#include <EasyEngine/eepch.h>
#include <EasyEngine/shader_manager/ShaderManagerOpenGL.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/shader_manager/Shader.h>

namespace easy_engine {
	namespace shader_manager {

		struct ShaderManagerOpenGL::Impl {
			Impl() {}

			std::vector<std::unique_ptr<Shader>> shaders_;
		};

		ShaderManagerOpenGL::ShaderManagerOpenGL()
			: p_impl_(new Impl()) {}

		ShaderManagerOpenGL::~ShaderManagerOpenGL() {}

		auto ShaderManagerOpenGL::LoadShader(std::string path, ShaderType type) -> const Shader & {
			auto shader = std::make_unique<Shader>();

			auto shader_source = resource_manager::ResourceManager::LoadFileAsString(path);
			shader->source = shader_source;
			shader->type = type;
			shader->id = this->p_impl_->shaders_.size();
			this->p_impl_->shaders_.push_back(std::move(shader));
			return *shader;
		}

		auto ShaderManagerOpenGL::AttachPipeline(const ShaderPipeline& pipeline) -> void {

		}

		auto ShaderManagerOpenGL::AttachShader(const Shader& shader, ShaderPipeline& pipeline) -> void {

		}

		auto ShaderManagerOpenGL::CreateShaderPipeline() -> const ShaderPipeline & {
			return *new ShaderPipeline();
		}

	}
}