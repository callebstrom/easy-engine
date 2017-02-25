#pragma once

#include <BaseDataTypes.h>

#ifndef RESOURCE_MANAGER_H
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
#endif // !RESOURCE_MANAGER_H