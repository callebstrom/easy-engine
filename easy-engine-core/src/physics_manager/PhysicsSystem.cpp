#include <EasyEngine/eepch.h>
#include <EasyEngine/physics_manager/PhysicsSystem.h>
#include <EasyEngine/ecs/component/RigidBodyComponent.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/physics_manager/PhysicsManager.h>
#include <EasyEngine/world/World.h>

namespace easy_engine {
	namespace physics_manager {

		PhysicsSystem::PhysicsSystem(Ref<PhysicsManager> physics_manager)
			: physics_manager_(physics_manager) {}

		auto PhysicsSystem::Update(float dt) -> void {
			for (auto const entity : this->entities_) {
				auto maybe_rigid_body_component = this->world->GetComponentForEntity<ecs::component::RigidBodyComponent>(entity);
				auto maybe_transform_component = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

				if (maybe_rigid_body_component.has_value() && maybe_transform_component.has_value()) {
					auto transform = maybe_transform_component.value();
					const auto rigid_body  = maybe_rigid_body_component.value();

					// TODO bullet causes dynamic debug library mismatch. Build all bullet3 projects with MTd
					this->physics_manager_->Register(
						rigid_body,
						transform
					);
					// Register rigid body in physics world (in PhysicsManager) https://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-a-physics-library/
				}
			}
		}
	}
}