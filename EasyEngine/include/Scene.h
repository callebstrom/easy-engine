#pragma once

#include <Renderable.h>
#include <map>
#include <IScene.h>

#ifndef SCENE_H
namespace easy_engine {
	namespace scene {
		class Scene : public virtual IScene {
			public:
				std::string name;
				float size;
				void Add(renderable::Renderable* renderable);
			protected:
				std::map<std::string, renderable::Renderable*> renderable_map; // Map containing renderables as value and reference as key
		};
	}
}
#endif // !SCENE_MANAGER_3D_H
