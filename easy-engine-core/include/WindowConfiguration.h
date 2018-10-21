#ifndef WINDOW_CONFIGURATION_H
#define WINDOW_CONFIGURATION_H
#pragma once

#include <Configuration.h>

namespace easy_engine {
	namespace configuration {
		enum WindowConfigurationParams : int {
			WIDTH,
			HEIGHT,
			TITLE
		};

		typedef Configuration<WindowConfigurationParams, std::string> WindowConfiguration_t;
	}
}
#endif // !WINDOW_CONFIGURATION_H
