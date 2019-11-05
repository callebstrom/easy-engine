#ifndef SHADER_H
#define SHADER_H
#pragma once

namespace easy_engine {
	namespace shader_manager {
		enum ShaderType {
			kVertex,
			kPixel,
			kGeometry,
			kTessEvaluation,
			kTessControl,
			kCompute
		};

		class Shader {
		public:

			Shader(int id, std::string source, ShaderType type)
				: id(id), source_(source), type(type) {}

			ShaderType type;
			unsigned int id;
			int diffuse_texture_sampler;
			int emissive_texture_sampler;

			auto GetSource() { return this->source_.c_str(); }
		private:
			std::string source_;

		};
	}
}

#endif // !SHADER_H

