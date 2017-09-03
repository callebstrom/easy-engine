#pragma once

#include <map>

#include <Configuration.h>

#ifndef RENDER_CONFIGURATION_H
namespace easy_engine {
	namespace render_manager {
		class RenderConfiguration : public configuration::Configuration {
			public:
				RenderConfiguration();
		};
	}
}
#endif // !RENDER_CONFIGURATION_H