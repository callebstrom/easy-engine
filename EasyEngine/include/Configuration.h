#pragma once

#include <map>
#include <string>

#ifndef CONFIGURATION_H
namespace easy_engine {
	namespace configuration {
		class Configuration {
			public:
				std::string Get(std::string key);
				void Set(std::string, std::string);
			protected:
				std::map<std::string, std::string> config_map_;
		};
	}
}
#endif // !CONFIGURATION_H