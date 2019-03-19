#ifndef ENTITY_H
#define ENTITY_H
#pragma once

namespace easy_engine {
	namespace entity {
		class Entity {
		public:
			float id;
			Entity(float id) { this->id = id; }
		};
	}
}

#endif // !ENTITY_H
