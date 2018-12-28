#include <EasyEngine/EasyEngine.h>

using namespace easy_engine;

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

class StaticSceneTest : public Application {
	public:
		StaticSceneTest() {

			renderable::Renderable3D* ptr = this->resource_manager_3d->LoadObj("..\\..\\EasyEngine\\easy-engine-core\\res\\basic_sword_low_poly.obj");
			this->scene_manager_3d->CreateScene("main");
			this->scene_manager_3d->Add(ptr, "main");
			this->scene_manager_3d->RenderScene();
		}

		~StaticSceneTest() {

		}
};


easy_engine::Application* easy_engine::CreateApplication() {
	easy_engine::Application* application = new StaticSceneTest();
	return application;
}