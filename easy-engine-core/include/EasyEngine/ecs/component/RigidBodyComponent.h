#pragma once

#include <EasyEngine/Common.h>
#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/resource/Mesh.h>

#include <Eigen/Core>

namespace easy_engine {
namespace ecs {
namespace component {

class EASY_ENGINE_API RigidBodyComponent : public Component {
 public:
  RigidBodyComponent(Eigen::Vector3f collision_shape,
                     Eigen::Vector3f collision_vector, float mass);
  auto GetCollisionShape() -> Eigen::Vector3f;
  auto GetMass() -> float;

 private:
  Eigen::Vector3f collision_vector_;
  float mass_;
  // TODO support mesh instead of box. Box is now created from Vector3f
  // dimensions
  Eigen::Vector3f collision_shape_;
};
}  // namespace component
}  // namespace ecs
}  // namespace easy_engine
