#include <Configuration.h>

namespace easy_engine {
	namespace configuration {
		std::string Configuration::Get(std::string key) {
			return this->config_map_[key];
		}
		void Configuration::Set(std::string key, std::string val) {
			this->config_map_[key] = val;
		}
	}
}