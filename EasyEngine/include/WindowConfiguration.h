#pragma once

#include <Configuration.h>

#ifndef WINDOW_CONFIGURATION_H
namespace easy_engine {
	namespace configuration {
		enum WindowConfigurationParams {
			WIDTH,
			HEIGHT,
			TITLE
		};

		typedef Configuration<WindowConfigurationParams, std::string> WindowConfiguration_t;
	}
}
#endif // !WINDOW_CONFIGURATION_H