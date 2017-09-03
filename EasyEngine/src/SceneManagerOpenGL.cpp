#include <SceneManagerOpenGL.h>
#include <thread>

namespace easy_engine {
	namespace scene_manager {
		SceneManagerOpenGL::SceneManagerOpenGL() {
			// TODO Reference to render manager should be fetched by service locater
			render_manager::RenderConfiguration* render_configuration = new render_manager::RenderConfiguration();
			this->render_manager = new render_manager::RenderManagerOpenGL(render_configuration);
		}

		void SceneManagerOpenGL::RenderScene() {
			
			this->render_manager->RenderQueuePush(this->current_scene->Get());

			this->render_manager->Render();
		}

		void SceneManagerOpenGL::CreateScene(std::string name) {
			Scene3DOpenGL* scene = new Scene3DOpenGL();
			this->scene_map.insert(std::make_pair(name, scene));

			if (current_scene == NULL)
				this->current_scene = scene;
		}
	}
}