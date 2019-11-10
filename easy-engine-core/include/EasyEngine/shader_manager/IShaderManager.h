#ifndef I_SHADER_MANAGER_H
#define I_SHADER_MANAGER_H
#pragma once

#include <EasyEngine/shader_manager/ShaderPipeline.h>

namespace easy_engine {
	namespace shader_manager {

		enum ShaderType;

		class IShaderManager {
		public:
			auto virtual LoadShaderByPath(std::string path, ShaderType type) -> Ref<Shader> = 0;
			auto virtual LoadShaderBySource(std::string source, ShaderType type) -> Ref<Shader> = 0;
			auto virtual AttachPipeline(Ref<ShaderPipeline> pipeline) -> void = 0;
			auto virtual LinkPipeline(Ref<ShaderPipeline> pipeline) -> void = 0;
			auto virtual AttachShader(Ref<Shader> shader, Ref<ShaderPipeline> pipeline) -> void = 0;
			auto virtual CreateShaderPipeline() -> Ref<ShaderPipeline> = 0;
			auto virtual GetAttachedPipeline() -> Ref<ShaderPipeline> = 0;
			auto virtual DeleteShader(Ref<Shader> shader) -> void = 0;
			auto virtual DeletePipeline(Ref<ShaderPipeline> shader_pipeline) -> void = 0;
		};
	}
}

#endif  // !I_SHADER_MANAGER_H
