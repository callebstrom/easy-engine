#include <EasyEngine/eepch.h>
#include <EasyEngine/component_manager/ComponentManager.h>

namespace easy_engine {
	namespace component_manager {
		void ComponentManager::RegisterEntity(entity::Entity* entity, std::unique_ptr<component::IComponent> component) {
			auto const component_ = std::move(component).get();
			this->registered_components_.push_back(component_);
			this->registered_entities_[this->registered_components_.size() - 1] = entity;
		}
	}
}