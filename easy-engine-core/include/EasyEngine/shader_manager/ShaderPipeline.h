#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H
#pragma once

#include <EasyEngine/Common.h>

namespace easy_engine {
	namespace shader_manager {

		class Shader;

		class EASY_ENGINE_API ShaderPipeline {
		public:
			ShaderPipeline(unsigned int internal_id);
			auto AddShader(Ref<Shader> shader) -> void;
			auto RemoveShader(Ref<Shader> shader) -> void;
			auto GetVertexShader() const -> Ref<Shader>;
			auto GetPixelShader() const -> Ref<Shader>;
			auto GetId() const -> unsigned int { return this->id; }
		private:
			unsigned int id;
			Ref<Shader> vertex_shader;
			Ref<Shader>pixel_shader;
			std::vector<Ref<Shader>> compute_shaders;
		};
	}
}

#endif // !SHADER_PIPELINE_H

