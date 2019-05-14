#pragma once

#include <chaiscript/chaiscript.hpp>

namespace easy_engine {
	namespace script_engine {
		class EASY_ENGINE_API ScriptEngine {
		public:
			void Eval(std::string source);
			ScriptEngine();
		private:
			chaiscript::ChaiScript chai;
			void RegisterApiTypes();
		};
	} 
}