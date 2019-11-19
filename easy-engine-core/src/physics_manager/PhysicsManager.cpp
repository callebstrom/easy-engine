#include <EasyEngine/eepch.h>
#include <EasyEngine/Common.h>
#include <EasyEngine/physics_manager/PhysicsManager.h>

#include <btBulletDynamicsCommon.h>

namespace easy_engine {
	namespace physics_manager {

		struct PhysicsManager::Impl {
			Scope<btDiscreteDynamicsWorld> dynamics_world;
		};

		PhysicsManager::PhysicsManager() {
			btBroadphaseInterface* broadphase = new btDbvtBroadphase();

			// Set up the collision configuration and dispatcher
			auto collisionConfiguration = new btDefaultCollisionConfiguration();
			auto collision_dispatcher = new btCollisionDispatcher(collisionConfiguration);

			// The actual physics solver
			auto constraint_solver = new btSequentialImpulseConstraintSolver;

			this->p_impl_->dynamics_world = CreateScope<btDiscreteDynamicsWorld>(collision_dispatcher, broadphase, constraint_solver, collisionConfiguration);
			this->p_impl_->dynamics_world->setGravity(btVector3(0, -9.81f, 0));
		}
	}
}