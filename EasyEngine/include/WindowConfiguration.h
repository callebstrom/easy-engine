#pragma once

#include <Configuration.h>

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