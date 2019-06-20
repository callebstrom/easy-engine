#ifndef BONE_H
#define BONE_H
#pragma once

namespace easy_engine {
	namespace resource {

		constexpr auto BONES_PER_VERTEX = 4;

		class EASY_ENGINE_API Bone {

		public:
			unsigned int identifiers[BONES_PER_VERTEX];
			float weights[BONES_PER_VERTEX];
			Bone() {};
		};
	}
}
#endif // !BONE_H