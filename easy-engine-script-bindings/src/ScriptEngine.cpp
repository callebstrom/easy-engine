#pragma once

#include <EasyEngine/eepch.h>
#include <EasyEngine/ScriptEngine.h>
#include <EasyEngine/EasyEngine.h>

namespace easy_engine {
	namespace script_engine {
		void ScriptEngine::Eval(std::string source)
		{
			this->chai.eval(source);
		}

		ScriptEngine::ScriptEngine()
		{
		}

		void ScriptEngine::RegisterApiTypes()
		{
			this->chai.add(chaiscript::user_type<Application>(), "Application");
		}
	}
}