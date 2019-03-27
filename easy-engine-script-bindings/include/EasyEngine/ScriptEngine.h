#pragma once

#include <chaiscript/chaiscript.hpp>

namespace easy_engine {
	namespace script_engine {
		class ScriptEngine {
		public:
			ScriptEngine();
		private:
			chaiscript::ChaiScript chai;
			void RegisterApiTypes();
		};
	}
}