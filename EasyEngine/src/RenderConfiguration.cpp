#include "RenderConfiguration.h"

namespace easy_engine {
	namespace configuration {
		RenderConfiguration::RenderConfiguration() {
			this->config_map_.insert(std::make_pair("resolution.x", "1024"));
			this->config_map_.insert(std::make_pair("resolution.y", "768"));
			this->config_map_.insert(std::make_pair("antialiasing", "4"));
		}
	}
}