#include <EasyEngine/eepch.h>
#include <EasyEngine/Common.h>
#include <EasyEngine/physics_manager/PhysicsManager.h>
#include <EasyEngine/ecs/entity/Entity.h>

#include <btBulletDynamicsCommon.h>

namespace easy_engine {
	namespace physics_manager {

		struct PhysicsManager::Impl {
			Scope<btDiscreteDynamicsWorld> dynamics_world;
		};

		PhysicsManager::PhysicsManager() {
			//btBroadphaseInterface* broadphase = new btDbvtBroadphase();

			//auto collisionConfiguration = new btDefaultCollisionConfiguration();
			//auto collision_dispatcher = new btCollisionDispatcher(collisionConfiguration);

			//auto constraint_solver = new btSequentialImpulseConstraintSolver;

			//this->p_impl_->dynamics_world = CreateScope<btDiscreteDynamicsWorld>(collision_dispatcher, broadphase, constraint_solver, collisionConfiguration);
			//this->p_impl_->dynamics_world->setGravity(btVector3(0, -9.81f, 0));
		}

		auto PhysicsManager::Register(Ref<ecs::component::RigidBodyComponent> rigid_body_component, Ref<ecs::component::TransformComponent> transform_component) -> void {
			/*btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
				btQuaternion(orientations[i].x, orientations[i].y, orientations[i].z, orientations[i].w),
				btVector3(positions[i].x, positions[i].y, positions[i].z)
			));

			btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
				0,                  // mass, in kg. 0 -> Static object, will never move.
				motionstate,
				boxCollisionShape,  // collision shape of body
				btVector3(0, 0, 0)    // local inertia
			);
			btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
			
			this->p_impl_->dynamics_world->addRigidBody(rigidBody);*/
		}
	}
}