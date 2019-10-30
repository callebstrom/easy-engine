#ifndef ENTITY_H
#define ENTITY_H
#pragma once

using EntityID = float;

namespace easy_engine {
	namespace entity {

		class EASY_ENGINE_API Entity {
		public:
			EntityID id;
			Entity(EntityID id) { this->id = id; }
		};
	}
}

#endif // !ENTITY_H
