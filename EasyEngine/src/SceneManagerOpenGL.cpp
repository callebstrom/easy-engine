#include <SceneManagerOpenGL.h>

namespace easy_engine {
	namespace scene_manager {

		void SceneManagerOpenGL::RenderScene() {

			render_manager::RenderManagerOpenGL* render_manager = dynamic_cast<render_manager::RenderManagerOpenGL*>(ManagerLocator::render_manager);
			
			for (auto &element : this->current_scene->Get())
				render_manager->AddRenderable(element);
			
			// Game loop
			while (true) {
				ManagerLocator::render_manager->Render();
			}
		}

		void SceneManagerOpenGL::CreateScene(std::string name) {
			Scene3DOpenGL* scene = new Scene3DOpenGL();
			this->scene_map.insert(std::make_pair(name, scene));

			if (current_scene == NULL)
				this->current_scene = scene;
		}
	}
}
