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
			ShaderType type;
			std::string source;
			int id;
		private:
			std::string source_path_;

		};
	}
}

#endif // !SHADER_H

