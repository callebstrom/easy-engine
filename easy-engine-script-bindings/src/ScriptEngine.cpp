#pragma once

#include <EasyEngine/eepch.h>
#include <EasyEngine/ScriptEngine.h>
#include <EasyEngine/EasyEngine.h>

namespace easy_engine {
	namespace script_engine {
		ScriptEngine::ScriptEngine() 
		{
			
		}
		void ScriptEngine::RegisterApiTypes()
		{
			// chai.add(chaiscript::user_type<Application>(), "Application");
		}
	}
}