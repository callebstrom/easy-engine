#include <EasyEngine/eepch.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/ecs/entity/EntityHandle.h>
#include <EasyEngine/ecs/entity/Entity.h>
#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/ecs/component_manager/ComponentManager.h>
#include <EasyEngine/ManagerLocator.h>

namespace easy_engine {
  namespace world {
    auto World::CreateEntity() -> entity::EntityHandle {
      auto id = this->entity_id_seq_++;
      entity::Entity* entity = new entity::Entity(id, "entity_" + std::to_string(id));
      return CreateEntity(entity);
    }

    auto World::CreateEntity(EntityName name)->entity::EntityHandle {
      entity::Entity* entity = new entity::Entity(this->entity_id_seq_++, name);
      return CreateEntity(entity);
    }

    auto World::CreateEntity(entity::Entity* entity)->entity::EntityHandle {
      this->entities_.push_back(entity);

      auto entity_handle = entity::EntityHandle();
      entity_handle.entity = entity;
      entity_handle.world = this;
      return entity_handle;
    }

    void World::RemoveEntity(entity::Entity const& entity) {}

    auto World::Update(float dt) const -> void {
      for (auto system : this->systems_) {
        system->Update(dt);
      }
    }

    auto World::SetupEnvironment(const resource::Environment& environment) -> void {
      event_manager::Event event;
      event.event_type = event_manager::EventType::kEnvironmentUpdate;

      event.data = reinterpret_cast<void*>(new resource::Environment(environment));

      ManagerLocator::event_manager->DispatchAsync(event);
    }
  }
}
