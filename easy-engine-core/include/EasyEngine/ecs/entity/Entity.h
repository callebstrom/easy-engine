#ifndef ENTITY_H
#define ENTITY_H
#pragma once

namespace easy_engine {
	namespace entity {
		class EASY_ENGINE_API Entity {
		public:
			float id;
			Entity(float id) { this->id = id; }
		};
	}
}

#endif // !ENTITY_H
