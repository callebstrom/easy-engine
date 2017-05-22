#include "RenderConfiguration.h"

namespace easy_engine {
	namespace configuration {
		RenderConfiguration::RenderConfiguration() {
			this->config_map_.insert(std::make_pair("resolution.x", "640"));
			this->config_map_.insert(std::make_pair("resolution.y", "600"));
			this->config_map_.insert(std::make_pair("antialiasing", "8"));
			this->config_map_.insert(std::make_pair(
				"vertex_shader.source_location", 
				"D:\\Dropbox\\Programmering\\EasyEngine\\EasyEngine\\src\\shaders\\vertex_shader.glsl"
			));
			this->config_map_.insert(std::make_pair(
				"fragment_shader.source_location",
				"D:\\Dropbox\\Programmering\\EasyEngine\\EasyEngine\\src\\shaders\\fragment_shader.glsl"
			));
		}
	}
}