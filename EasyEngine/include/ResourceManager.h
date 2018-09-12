#pragma once

#include <Common.h>

namespace easy_engine {
	namespace resource_manager {
		class ResourceManager
		{
			protected:
				byte* resourceCache;
				std::string base_path_;
				byte * LoadResourceByName(std::string pathRelativeToBase);
		};
	}
}