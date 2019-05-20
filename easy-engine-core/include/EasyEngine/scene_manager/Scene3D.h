#ifndef SCENE3D_H
#define SCENE3D_H
#pragma once

#include <EasyEngine/scene_manager/Scene.h>
#include <EasyEngine/resource/Mesh.h>
#include <EasyEngine/scene_manager/RootNode.h>
#include <EasyEngine/scene_manager/RenderableNode.h>
#include <EasyEngine/scene_manager/SceneGraph3D.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

namespace easy_engine {
	namespace scene_manager {

		class EASY_ENGINE_API Scene3D : public Scene {
			friend class SceneManager3D;
		public:
			Scene3D();
		};
	}
}

#endif