#ifndef I_SHADER_MANAGER_H
#define I_SHADER_MANAGER_H
#pragma once

#include <EasyEngine/shader_manager/ShaderPipeline.h>

namespace easy_engine {
	namespace shader_manager {

		enum ShaderType;

		class IShaderManager {
		public:
			auto virtual LoadShader(std::string path, ShaderType type) -> Ref<Shader> = 0;
			auto virtual AttachPipeline(Ref<ShaderPipeline> pipeline) -> void = 0;
			auto virtual LinkPipeline(Ref<ShaderPipeline> pipeline) -> void = 0;
			auto virtual AttachShader(Ref<Shader> shader, Ref<ShaderPipeline> pipeline) -> void = 0;
			auto virtual CreateShaderPipeline() -> Ref<ShaderPipeline> = 0;
		};
	}
}

#endif  // !I_SHADER_MANAGER_H
