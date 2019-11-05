#include <EasyEngine/eepch.h>
#include <EasyEngine/shader_manager/ShaderPipeline.h>
#include <EasyEngine/shader_manager/Shader.h>

namespace easy_engine {
	namespace shader_manager {

		ShaderPipeline::ShaderPipeline(unsigned int id)
			: id(id) {};

		auto ShaderPipeline::AddShader(Ref<Shader> shader) -> void {
			switch (shader->type) {
			case ShaderType::kVertex:
				this->vertex_shader = shader;
				break;
			case ShaderType::kPixel:
				this->pixel_shader = shader;
				break;
			}
		}
		auto ShaderPipeline::RemoveShader(Ref<Shader> shader) -> void {
			switch (shader->type) {
			case ShaderType::kVertex:
				this->vertex_shader = nullptr;
				break;
			case ShaderType::kPixel:
				this->pixel_shader = nullptr;
			}
		}

		auto ShaderPipeline::GetVertexShader() const -> Ref<Shader> {
			return this->vertex_shader;
		}

		auto ShaderPipeline::GetPixelShader() const -> Ref<Shader> {
			return this->pixel_shader;
		}
	}
}
