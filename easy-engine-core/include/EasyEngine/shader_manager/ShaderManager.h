#include <EasyEngine/shader_manager/ShaderPipeline.h>

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#pragma once

namespace easy_engine {
	namespace shader_manager {

		class IShaderManager {
		public:
			auto virtual LoadShader(std::string path) -> const Shader & = 0;
			auto virtual AttachPipeline(const ShaderPipeline& pipeline) -> void = 0;
			auto virtual AttachShader(const Shader& shader, ShaderPipeline& pipeline) -> void = 0;
			auto virtual CreateShaderPipeline() -> const ShaderPipeline & = 0;
		};
	}
}

#endif  // !SHADER_MANAGER_H
