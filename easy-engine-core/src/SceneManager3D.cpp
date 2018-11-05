#include <EasyEngine/scene_manager/SceneManager3D.h>

namespace easy_engine {
	namespace scene_manager {

		logger::Logger* SceneManager3D::log = new logger::Logger("SceneManager3D");

		void SceneManager3D::RenderScene() {

			render_manager::RenderManagerOpenGL* render_manager = static_cast<render_manager::RenderManagerOpenGL*>(ManagerLocator::render_manager);

			// Game loop
			while (true) {
				ManagerLocator::input_manager->PollEvents();
				static_cast<Scene3D*>(this->current_scene)->scene_graph_->traverse();
				ManagerLocator::window_manager->SwapBuffers(); // should perhaps be triggered as post-render callback?
			}
		}

		void SceneManager3D::CreateScene(std::string name) {
			Scene3D* scene = new Scene3D();
			this->scene_map.insert(std::make_pair(name, scene));

			if (current_scene == NULL)
				this->current_scene = scene;
		}
	}
}
