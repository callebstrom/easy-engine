#include <EasyEngine/eepch.h>
#include <EasyEngine/component_manager/ComponentManager.h>

namespace easy_engine {
	namespace component_manager {
		template<typename Component>
		void ComponentManager<Component>::RegisterEntity(entity::Entity& entity, Component&& component) {
			this->registered_components_.push_back(component);
			this->registered_entities_[this->registered_components_.size() - 1] = entity;
		}
	}
}