#pragma once


#include <Configuration.h>

#ifndef RENDER_CONFIGURATION_H
namespace easy_engine {
	namespace configuration {
		enum RenderConfigurationParams : int {
			RESOLUTION_X,
			RESOLUTION_Y,
			ANTIALIASING,
			VERTEX_SHADER_SOURCE_LOCATION,
			FRAGMENT_SHADER_SOURCE_LOCATION
		};

		typedef Configuration<int, std::string> RenderConfiguration_t;
	}
}
#endif // !RENDER_CONFIGURATION_H