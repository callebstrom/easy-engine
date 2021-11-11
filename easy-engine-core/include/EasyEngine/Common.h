#pragma once

#include <EasyEngine/ecs/component/Component.h>

template <typename OrderedDataType>
using OrderedTypeMap = std::map<std::type_index, OrderedDataType>;

using ComponentSignature = std::bitset<2048>;

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

struct ComponentSignatureComparetor {
  bool operator()(const ComponentSignature& left,
                  const ComponentSignature& right) const {
    for (unsigned int i = 0; i < left.size(); i++) {
      if (left.test(i)) {
        if (!right.test(i)) return false;
      } else {
        if (right.test(i)) return true;
      }
      return false;
    }
  }
};

namespace easy_engine {
inline void Replace(std::string& string, std::string search,
                    std::string replacement) {
  size_t pos = string.find(search);
  while (pos != std::string::npos) {
    string.replace(pos, search.size(), replacement);
    pos = string.find(search, pos + replacement.size());
  }
}
}  // namespace easy_engine
