#include <EasyEngine/eepch.h>
#include <EasyEngine/Common.h>
#include <EasyEngine/ecs/entity/Entity.h>
#include <EasyEngine/physics_manager/PhysicsManager.h>
#include <btBulletDynamicsCommon.h>

namespace easy_engine {
namespace physics_manager {

struct PhysicsManager::Impl {
  Scope<btDiscreteDynamicsWorld> dynamics_world;
};

PhysicsManager::PhysicsManager() {
   btBroadphaseInterface* broadphase = new btDbvtBroadphase();

   auto collisionConfiguration = new btDefaultCollisionConfiguration();
   auto collision_dispatcher = new
   btCollisionDispatcher(collisionConfiguration);

   auto constraint_solver = new btSequentialImpulseConstraintSolver;

   this->p_impl_->dynamics_world =
   CreateScope<btDiscreteDynamicsWorld>(collision_dispatcher, broadphase,
   constraint_solver, collisionConfiguration);
   this->p_impl_->dynamics_world->setGravity(btVector3(0, -9.81f, 0));
}

auto PhysicsManager::Register(
    Ref<ecs::component::RigidBodyComponent> rigid_body_component,
    Ref<ecs::component::TransformComponent> transform_component) -> void {
  auto quaternion = transform_component->GetRotation();
  auto axis = quaternion.axis();
  auto angle = quaternion.angle();
  auto translation = transform_component->GetTranslation();

  btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
      btQuaternion(axis.x(), axis.y(), axis.z(), angle),
      btVector3(translation.x(), translation.y(), translation.z())));

  auto collision_shape = rigid_body_component->GetCollisionShape();
  btCollisionShape* boxCollisionShape = new btBoxShape(
      btVector3(collision_shape.x(), collision_shape.y(), collision_shape.z()));
  btVector3 inertia(0, 0, 0);

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
      rigid_body_component->GetMass(), motionstate, boxCollisionShape, inertia);
  btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);

  this->p_impl_->dynamics_world->addRigidBody(rigidBody);
}
}  // namespace physics_manager
}  // namespace easy_engine