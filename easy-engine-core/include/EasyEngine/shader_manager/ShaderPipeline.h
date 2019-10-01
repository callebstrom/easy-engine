#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H
#pragma once

namespace easy_engine {
	namespace shader_manager {

		class Shader;

		class ShaderPipeline {
		public:
			auto AddShader(const Shader& shader) -> void;
			auto RemoveShader(const Shader& shader) -> void;
		private:
			std::shared_ptr<Shader> vertex_shader;
			std::shared_ptr<Shader> pixel_shader;
			std::vector<std::shared_ptr<Shader>> compute_shaders;
		};
	}
}

#endif // !SHADER_PIPELINE_H

