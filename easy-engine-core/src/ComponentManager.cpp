#include <EasyEngine/eepch.h>
#include <EasyEngine/ecs/component_manager/ComponentManager.h>
#include <EasyEngine/ecs/entity/Entity.h>

namespace easy_engine {
	namespace component_manager {
		void ComponentManager::RegisterEntity(entity::Entity* entity, std::shared_ptr<component::Component> component) {
			this->registered_components_.emplace_back(component);
			this->entity_id_component_index_map_[entity->id] = this->registered_components_.size() - 1;
		}
	}
}