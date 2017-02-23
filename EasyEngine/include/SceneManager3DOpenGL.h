#pragma once

#include <RenderManagerOpenGL.h>
#include <SceneManager3D.h>
#include <Renderable3DOpenGL.h>
#include <Scene3DOpenGL.h>
#include <RenderConfiguration.h>

#ifndef SCENE_MANAGER_3D_OPEN_GL_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManager3DOpenGL : public SceneManager3D {
			public:
				void RenderScene();
				void CreateScene(std::string name);
				SceneManager3DOpenGL();
			private:
				render_manager::RenderManagerOpenGL* render_manager;
		};
	}
}
#endif // !SCENE_MANAGER_3D_OPEN_GL_H
