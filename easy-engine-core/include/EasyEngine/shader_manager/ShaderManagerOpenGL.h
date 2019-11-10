#ifndef SHADER_MANAGER_OPEN_GL_H
#define SHADER_MANAGER_OPEN_GL_H
#pragma once

#include <EasyEngine/shader_manager/IShaderManager.h>

namespace easy_engine {
	namespace shader_manager {
		class ShaderManagerOpenGL : public IShaderManager {
		public:
			ShaderManagerOpenGL::ShaderManagerOpenGL();
			ShaderManagerOpenGL::~ShaderManagerOpenGL();

			Ref<Shader> LoadShaderByPath(std::string path, ShaderType type) override;
			Ref<Shader> LoadShaderBySource(std::string source, ShaderType type) override;
			Ref<ShaderPipeline> CreateShaderPipeline() override;
			Ref<ShaderPipeline> GetAttachedPipeline() override;
			void LinkPipeline(Ref<ShaderPipeline> pipeline) override;
			void AttachPipeline(Ref<ShaderPipeline> pipeline) override;
			void AttachShader(Ref<Shader> shader, Ref<ShaderPipeline> pipeline) override;
			void DeleteShader(Ref<Shader> shader) override;
			void DeletePipeline(Ref<ShaderPipeline> shader_pipeline) override;

		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif // !SHADER_MANAGER_OPEN_GL_H