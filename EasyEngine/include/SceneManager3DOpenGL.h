#pragma once

#include <RenderManagerOpenGL.h>
#include <SceneManager3D.h>
#include <Renderable3DOpenGL.h>

#ifndef SCENE_MANAGER_3D_OPEN_GL_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManager3DOpenGL : public SceneManager3D {
			private:
				render_manager::RenderManagerOpenGL* render_manager;
			public:
				void Add(renderable::Renderable* renderable, std::string scene_name); // Adds renderable object to given scene
				void Add(renderable::Renderable* renderable); // Adds renderable object to current scene
				void LoadScene();
		};
	}
}
#endif // !SCENE_MANAGER_3D_OPEN_GL_H
