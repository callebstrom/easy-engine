#pragma once

#include <thread>

#include <RenderManagerOpenGL.h>
#include <SceneManager.h>
#include <Renderable3D.h>
#include <Scene3DOpenGL.h>
#include <RenderConfiguration.h>
#include <SceneConfiguration.h>

using easy_engine::configuration::SceneConfiguration_t;

#ifndef SCENE_MANAGER_OPEN_GL_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManagerOpenGL : public SceneManager {
			public:
				void RenderScene();
				void CreateScene(std::string name);
				SceneManagerOpenGL(SceneConfiguration_t* configuration);
			private:
				render_manager::RenderManagerOpenGL* render_manager;
		};
	}
}
#endif // !SCENE_MANAGER_3D_OPEN_GL_H
