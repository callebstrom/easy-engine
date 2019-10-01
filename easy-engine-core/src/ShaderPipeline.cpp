#include <EasyEngine/eepch.h>
#include <EasyEngine/shader_manager/ShaderPipeline.h>
#include <EasyEngine/shader_manager/Shader.h>

namespace easy_engine {
	namespace shader_manager {
		void ShaderPipeline::AddShader(const Shader& shader) {
			switch (shader.type) {
			case ShaderType::kVertex:
				this->vertex_shader = std::make_shared<Shader>(shader);
				break;
			}
		}
		void ShaderPipeline::RemoveShader(const Shader& shader) {
			switch (shader.type) {
			case ShaderType::kVertex:
				this->vertex_shader = nullptr;
				break;
			}
		}
	}
}
