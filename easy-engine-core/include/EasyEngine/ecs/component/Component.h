#pragma once

#include <EasyEngine/Common.h>

namespace easy_engine {
namespace ecs {
namespace component {

struct EASY_ENGINE_API ComponentCounter {
  static int familyCounter;
};

class EASY_ENGINE_API Component {
 public:
  Component() = default;
  virtual ~Component() = default;
  Component(const Component&) = default;
  Component& operator=(const Component&) = default;
  Component(Component&&) = default;
  Component& operator=(Component&&) = default;
  float id;

  template <typename ComponentType,
            typename std::enable_if<std::is_base_of<
                Component, ComponentType>::value>::type* = nullptr>
  static int GetComponentFamily() {
    static int family = ComponentCounter::familyCounter++;
    return family;
  }
};

}  // namespace component
}  // namespace ecs
}  // namespace easy_engine
