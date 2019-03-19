#ifndef ABSTRACT_COMPONENT_MANAGER_H
#define ABSTRACT_COMPONENT_MANAGER_H
#pragma once

namespace easy_engine {
	namespace component_manager {
		class AbstractComponentManager {
		public:
			AbstractComponentManager() = default;
			virtual ~AbstractComponentManager() = default;
			AbstractComponentManager(const AbstractComponentManager&) = default;
			AbstractComponentManager& operator=(const AbstractComponentManager&) = default;
			AbstractComponentManager(AbstractComponentManager&&) = default;
			AbstractComponentManager& operator=(AbstractComponentManager&&) = default;
		};
	}
}

#endif // !ABSTRACT_COMPONENT_MANAGER_H

