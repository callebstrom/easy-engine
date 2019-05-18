#include <EasyEngine/eepch.h>
#include <EasyEngine/component_manager/ComponentManager.h>

namespace easy_engine {
	namespace component_manager {
		void ComponentManager::RegisterEntity(entity::Entity* entity, std::shared_ptr<component::IComponent> component) {
			this->registered_components_.emplace_back(component);
			this->registered_entities_[this->registered_components_.size() - 1] = entity;
		}
	}
}