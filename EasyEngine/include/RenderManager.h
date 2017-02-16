#pragma once
#include <IRenderManager.h>
#include <cstdlib>

#ifndef RENDER_MANAGER
namespace easy_engine {
	namespace configuration {
		class RenderConfiguration;
	}
	namespace render_manager {
		class RenderManager : public IRenderManager {
			protected:
				configuration::RenderConfiguration* render_config_;
				
		};
	}
}
#endif // !RENDER_MANAGER