#include <SceneManagerOpenGL.h>
#include <thread>

using easy_engine::configuration::SceneConfigurationParams;

namespace easy_engine {
	namespace scene_manager {

		typedef configuration::RenderConfigurationParams r_config_params_t;

		SceneManagerOpenGL::SceneManagerOpenGL(SceneConfiguration_t* configuration) {
			// TODO Reference to render manager should be fetched by service locater
			configuration::RenderConfiguration_t* render_configuration = new configuration::RenderConfiguration_t();
			
			render_configuration->Set(r_config_params_t::RESOLUTION_X, configuration->Get(SceneConfigurationParams::SCENE_RESOLUTION_X));
			render_configuration->Set(r_config_params_t::RESOLUTION_Y, configuration->Get(SceneConfigurationParams::SCENE_RESOLUTION_X));
			render_configuration->Set(r_config_params_t::ANTIALIASING, "8");
			render_configuration->Set(r_config_params_t::VERTEX_SHADER_SOURCE_LOCATION, "D:\\Dropbox\\dev\\EasyEngine\\EasyEngine\\src\\shaders\\vertex_shader.glsl");
			render_configuration->Set(r_config_params_t::FRAGMENT_SHADER_SOURCE_LOCATION, "D:\\Dropbox\\dev\\EasyEngine\\EasyEngine\\src\\shaders\\fragment_shader.glsl");

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
