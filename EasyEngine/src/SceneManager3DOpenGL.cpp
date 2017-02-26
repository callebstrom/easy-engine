#include <SceneManager3DOpenGL.h>
#include <thread>

namespace easy_engine {
	namespace scene_manager {
		SceneManager3DOpenGL::SceneManager3DOpenGL() {
			// TODO Reference to render manager should be fetched by service locater
			configuration::RenderConfiguration* render_configuration = new configuration::RenderConfiguration();
			this->render_manager = new render_manager::RenderManagerOpenGL(render_configuration);
		}

		void SceneManager3DOpenGL::RenderScene() {
			
			this->render_manager->RenderQueuePush(this->current_scene->Get());

			this->render_manager->Render();
		}

		void SceneManager3DOpenGL::CreateScene(std::string name) {
			scene::Scene3DOpenGL* scene = new scene::Scene3DOpenGL();
			this->scene_map.insert(std::make_pair(name, scene));

			if (current_scene == NULL)
				this->current_scene = scene;
		}
	}
}