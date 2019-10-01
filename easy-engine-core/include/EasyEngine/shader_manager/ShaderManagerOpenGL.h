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

			const Shader& LoadShader(std::string path, ShaderType type) override;
			void AttachPipeline(const ShaderPipeline& pipeline) override;
			void AttachShader(const Shader& shader, ShaderPipeline& pipeline) override;
			const ShaderPipeline& CreateShaderPipeline() override;

		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif // !SHADER_MANAGER_OPEN_GL_H