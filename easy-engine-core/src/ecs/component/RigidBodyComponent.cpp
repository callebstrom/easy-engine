#include <EasyEngine/eepch.h>
#include <EasyEngine/ecs/component/RigidBodyComponent.h>

namespace easy_engine {
namespace ecs {
namespace component {
RigidBodyComponent::RigidBodyComponent(Eigen::Vector3f collision_shape,
                                       Eigen::Vector3f collision_vector,
                                       float mass)
    : collision_shape_(collision_shape),
      collision_vector_(collision_vector),
      mass_(mass) {}
auto RigidBodyComponent::GetCollisionShape() -> Eigen::Vector3f {
  return collision_shape_;
}
auto RigidBodyComponent::GetMass() -> float { return mass_; }
}  // namespace component
}  // namespace ecs
}  // namespace easy_engine
