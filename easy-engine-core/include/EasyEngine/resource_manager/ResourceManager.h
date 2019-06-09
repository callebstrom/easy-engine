#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

namespace easy_engine {
	namespace resource_manager {

		class EASY_ENGINE_API ResourceManager {
		protected:
			byte* resourceCache;
			byte* LoadResourceByName(std::string pathRelativeToBase);
		};
	}
}
#endif // !RESOURCE_MANAGER_H
