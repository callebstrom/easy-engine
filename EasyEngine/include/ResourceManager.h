#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

#include <Common.h>

namespace easy_engine {
	namespace resource_manager {
		class ResourceManager
		{
		protected:
			byte* resourceCache;
			byte* LoadResourceByName(std::string pathRelativeToBase);
		};
	}
}
#endif // !RESOURCE_MANAGER_H
