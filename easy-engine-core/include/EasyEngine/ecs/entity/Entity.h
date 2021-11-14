#ifndef ENTITY_H
#define ENTITY_H
#pragma once

using EntityID = float;
using EntityName = std::string;

namespace easy_engine {
  namespace entity {

    class EASY_ENGINE_API Entity {
    public:
      EntityID id;
      EntityName name;
      Entity(EntityID id, EntityName name) : id(id), name(name) {};
    };
  }
}

#endif // !ENTITY_H
