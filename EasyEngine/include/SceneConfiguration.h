#pragma once

#include <Configuration.h>

#ifndef RENDER_CONFIGURATION_H
namespace easy_engine {
	namespace configuration {
		enum SceneConfigurationParams : int {
			SCENE_RESOLUTION_X,
			SCENE_RESOLUTION_Y
		};

		typedef Configuration<int, std::string> SceneConfiguration_t;
	}
}
#endif // !RENDER_CONFIGURATION_H