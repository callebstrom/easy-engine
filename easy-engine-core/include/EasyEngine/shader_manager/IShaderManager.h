#include <EasyEngine/shader_manager/ShaderPipeline.h>

#ifndef I_SHADER_MANAGER_H
#define I_SHADER_MANAGER_H
#pragma once

namespace easy_engine {
	namespace shader_manager {

		enum ShaderType;

		class IShaderManager {
		public:
			auto virtual LoadShader(std::string path, ShaderType type) -> const Shader & = 0;
			auto virtual AttachPipeline(const ShaderPipeline& pipeline) -> void = 0;
			auto virtual AttachShader(const Shader& shader, ShaderPipeline& pipeline) -> void = 0;
			auto virtual CreateShaderPipeline() -> const ShaderPipeline & = 0;
		};
	}
}

#endif  // !I_SHADER_MANAGER_H
