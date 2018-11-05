#include <EasyEngine/Application.h>

using easy_engine::configuration::WindowConfiguration_t;
using easy_engine::configuration::WindowConfigurationParams;
using easy_engine::render_manager::RenderManagerOpenGL;
using easy_engine::render_manager::RenderManager;
using easy_engine::window_manager::WindowManager;
using easy_engine::window_manager::WindowManagerGLFW;
using easy_engine::configuration::RenderConfiguration_t;
using easy_engine::configuration::RenderConfigurationParams;
using easy_engine::input_manager::InputManager;
using easy_engine::scene_manager::SceneManager3D;
using easy_engine::input_manager::InputManager;
using easy_engine::resource_manager::ResourceManager3D;
using easy_engine::renderable::Renderable3D;

class StaticSceneTest : public easy_engine::Application {
	public:
		StaticSceneTest() {

		}

		~StaticSceneTest() {

		}
};


easy_engine::Application* easy_engine::CreateApplication() {
	easy_engine::Application* application = new StaticSceneTest();
	return application;
}