#include <EasyEngine/eepch.h>
#include <EasyEngine/Application.h>

namespace easy_engine {

	Application::Application() {

		logger::Logger::Init();

		configuration::RenderConfiguration_t* render_configuration = new configuration::RenderConfiguration_t();
		render_configuration->Set(configuration::RenderConfigurationParams::RESOLUTION_X, "1920");
		render_configuration->Set(configuration::RenderConfigurationParams::RESOLUTION_Y, "1080");
		render_configuration->Set(configuration::RenderConfigurationParams::ANTIALIASING, "8");
		render_configuration->Set(configuration::RenderConfigurationParams::VERTEX_SHADER_SOURCE_LOCATION, "shaders\\vertex_shader.glsl");
		render_configuration->Set(configuration::RenderConfigurationParams::FRAGMENT_SHADER_SOURCE_LOCATION, "shaders\\fragment_shader.glsl");

		configuration::WindowConfiguration_t* window_configuration = new configuration::WindowConfiguration_t();
		window_configuration->Set(configuration::WindowConfigurationParams::WIDTH, "1920");
		window_configuration->Set(configuration::WindowConfigurationParams::HEIGHT, "1080");

		this->scene_manager_3d = new scene_manager::SceneManager3D();
		this->resource_manager_3d = new resource_manager::ResourceManager3D();
		this->input_manager = new input_manager::InputManager();
		this->window_manager = new window_manager::WindowManagerGLFW();
		this->window_manager->CreateWindowEE(window_configuration);
		this->render_manager = new render_manager::RenderManagerOpenGL(render_configuration);

		ManagerLocator::render_manager = dynamic_cast<render_manager::RenderManager*>(this->render_manager);
		ManagerLocator::input_manager = this->input_manager;
		ManagerLocator::window_manager = dynamic_cast<window_manager::WindowManager*>(this->window_manager);
	}

	Application::~Application() {
	}

	void Application::Run() {
		this->is_running_ = true;
		while (this->is_running_) {
			this->scene_manager_3d->RenderScene();
		}
	}

}