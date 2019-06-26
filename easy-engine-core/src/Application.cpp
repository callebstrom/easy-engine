#include <EasyEngine/eepch.h>
#include <EasyEngine/Application.h>
#include <EasyEngine/render_manager/RenderSystem.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <experimental/filesystem>

namespace easy_engine {

	Application::Application() {
		logger::Logger::Init();
		this->event_manager = new event_manager::EventManager();
		ManagerLocator::event_manager = this->event_manager;

		this->scene_manager_3d = new scene_manager::SceneManager3D();
		this->resource_manager_3d = new resource_manager::ResourceManager3D();
		this->input_manager = new input_manager::InputManager();
		this->world = new world::World();

		this->InitializeDefaultSystems();
	}

	Application::~Application() {

	}

	void Application::Run() {

		configuration::RenderConfiguration_t* render_configuration = new configuration::RenderConfiguration_t();
		render_configuration->Set(configuration::RenderConfigurationParams::RESOLUTION_X, "1024");
		render_configuration->Set(configuration::RenderConfigurationParams::RESOLUTION_Y, "768");
		render_configuration->Set(configuration::RenderConfigurationParams::ANTIALIASING, "8");
		render_configuration->Set(configuration::RenderConfigurationParams::VERTEX_SHADER_SOURCE_LOCATION, Application::GetEngineDirectory() + "\\easy-engine-core\\src\\shaders\\vertex_shader.glsl");
		render_configuration->Set(configuration::RenderConfigurationParams::FRAGMENT_SHADER_SOURCE_LOCATION, Application::GetEngineDirectory() + "\\easy-engine-core\\src\\shaders\\fragment_shader.glsl");

		configuration::WindowConfiguration_t * window_configuration = new configuration::WindowConfiguration_t();
		window_configuration->Set(configuration::WindowConfigurationParams::WIDTH, "1024");
		window_configuration->Set(configuration::WindowConfigurationParams::HEIGHT, "768");

		this->window_manager = new window_manager::WindowManagerGLFW();
		this->window_manager->CreateWindowEE(window_configuration);
		this->render_manager = new render_manager::RenderManagerOpenGL(render_configuration);

		ManagerLocator::render_manager = dynamic_cast<render_manager::RenderManager*>(this->render_manager);
		ManagerLocator::input_manager = this->input_manager;
		ManagerLocator::window_manager = dynamic_cast<window_manager::WindowManager*>(this->window_manager);

		this->is_running_ = true;
		EE_CORE_INFO("Application is now running");

		std::chrono::high_resolution_clock timer;
		using ms = std::chrono::duration<float, std::milli>;

		auto start = timer.now();
		auto stop = timer.now();
		float deltaTime = 0;

		while (this->is_running_) {

			this->event_manager->ConsumeEventBuffer(event_manager::EventType::EnvironmentUpdate);

			deltaTime = std::chrono::duration_cast<ms>(stop - start).count();
			start = timer.now();

			this->input_manager->PollEvents();
			this->event_manager->ConsumeEventBuffer(event_manager::EventType::Keyboard);
			this->world->Update(deltaTime);
			this->event_manager->ConsumeEventBuffer(event_manager::EventType::_3DPreRender);
			this->event_manager->ConsumeEventBuffer(event_manager::EventType::_3DObjectRenderable);
			this->event_manager->ConsumeEventBuffer(event_manager::EventType::_3DPostRender);
			event_manager::Event event = event_manager::Event();
			event.event_type = event_manager::EventType::GlobalTick;
			this->event_manager->Dispatch(event);

			stop = timer.now();
		}

		this->window_manager->CloseWindowEE();
	}

	std::future<void> Application::RunAsync() {
		return std::async([this]() -> void {
			this->Run();
			});
	}

	std::string Application::GetEngineDirectory()
	{
		return std::experimental::filesystem::current_path().remove_filename().u8string();
	}

	void Application::InitializeDefaultSystems()
	{
		auto render_system = new render_manager::RenderSystem();
		world->AddSystem<ecs::component::MeshComponent, ecs::component::TransformComponent>(render_system);
	}

	void Application::Close() {
		this->is_running_ = false;
	}

}