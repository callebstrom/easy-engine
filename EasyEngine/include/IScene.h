#pragma once

#include <Renderable.h>
#include <map>

#ifndef SCENE_H
namespace easy_engine {
	namespace scene {
		class IScene {
		public:
			virtual void Add(renderable::Renderable*) = 0;

		};
	}
}
#endif // !SCENE_MANAGER_3D_H
