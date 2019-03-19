#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#pragma once

namespace easy_engine {

	namespace entity {
		class Entity;
	}

	namespace component_manager {
		template <typename ComponentType>

		class IComponentManager {
		public:
			inline virtual void Render(float dt) = 0;
			inline virtual void Update(float dt) = 0;
			void RegisterEntity(entity::Entity& entity, ComponentType && component) { this->registered_entities_.push_back(entity); }
		protected:
			std::vector<entity::Entity*> registered_entities_;
		};
	}
}
#endif // !COMPONENT_MANAGER_H
