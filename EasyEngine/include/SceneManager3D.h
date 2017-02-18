#pragma once

#include <RenderManagerOpenGL.h>
#include <SceneManager.h>

#ifndef SCENE_MANAGER_3D_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManager3D : public SceneManager {
			private:
				render_manager::RenderManagerOpenGL* render_manager_open_gl; // Maintain referens to render manager in order to render current_scene
		};
	}
}
#endif // !SCENE_MANAGER_3D_H
