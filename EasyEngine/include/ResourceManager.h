#pragma once
#include <IResourceManager.h>
#include <BaseDataTypes.h>

#ifndef RESOURCE_MANAGER_H
namespace easy_engine {
	namespace resource_manager {
		class ResourceManager : public IResourceManager
		{
			protected:
				byte* resourceCache;
				std::string base_path_;
				byte * LoadResourceByName(std::string pathRelativeToBase);
		};
	}
}
#endif // !RESOURCE_MANAGER_H