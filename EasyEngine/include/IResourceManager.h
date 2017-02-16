#pragma once
#include <BaseDataTypes.h>

#ifndef I_RESOURCE_MANAGER_H
namespace easy_engine {
	namespace resource_manager {
		class IResourceManager {
		protected:
			virtual byte* LoadResourceByName(std::string fullResourcePath) = 0;
		};
	}
}
#endif // !I_RESOURCE_MANAGER_H