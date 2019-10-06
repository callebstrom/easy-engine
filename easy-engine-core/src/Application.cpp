#include <EasyEngine/eepch.h>

#include <EasyEngine/Application.h>
#include <EasyEngine/render_manager/RenderSystem.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/shader_manager/ShaderManagerOpenGL.h>
#include <EasyEngine/ui/UIRenderManagerOpenGL.h>
#include <EasyEngine/ui/UIRenderSystem.h>

#include <experimental/filesystem>

namespace easy_engine {

	Application::Application() {
		logger::Logger::Init();
		this->event_manager = std::make_shared<event_manager::EventManager>();
		ManagerLocator::event_manager = this->event_manager.get();

		this->scene_manager_3d = new scene_manager::SceneManager3D();
		this->resource_manager_3d = new resource_manager::ResourceManager3D();
		this->input_manager = std::make_shared<input_manager::InputManager>();
		this->world = new world::World();
	}

	Application::~Application() {

	}

	void Application::Run() {

		configuration::RenderConfiguration_t* render_configuration = new configuration::RenderConfiguration_t();
		render_configuration->Set(configuration::RenderConfigurationParams::RESOLUTION_X, "1920");
		render_configuration->Set(configuration::RenderConfigurationParams::RESOLUTION_Y, "1080");
		render_configuration->Set(configuration::RenderConfigurationParams::ANTIALIASING, "16");
		render_configuration->Set(configuration::RenderConfigurationParams::VERTEX_SHADER_SOURCE_LOCATION, Application::GetEngineDirectory() + "\\easy-engine-core\\src\\shaders\\vertex_shader.glsl");
		render_configuration->Set(configuration::RenderConfigurationParams::FRAGMENT_SHADER_SOURCE_LOCATION, Application::GetEngineDirectory() + "\\easy-engine-core\\src\\shaders\\fragment_shader.glsl");

		configuration::WindowConfiguration_t* window_configuration = new configuration::WindowConfiguration_t();
		window_configuration->Set(configuration::WindowConfigurationParams::WIDTH, "1920");
		window_configuration->Set(configuration::WindowConfigurationParams::HEIGHT, "1080");

		this->shader_manager = std::make_shared<shader_manager::ShaderManagerOpenGL>();
		this->window_manager = std::make_shared<window_manager::WindowManagerGLFW>(this->event_manager, this->input_manager);
		this->ui_render_manager = std::make_shared<ui::UIRenderManagerOpenGL>(this->window_manager, this->event_manager);

		this->InitializeDefaultSystems();

		this->window_manager->CreateWindowEE(window_configuration);
		this->render_manager = new render_manager::RenderManagerOpenGL(
			render_configuration,
			std::static_pointer_cast<shader_manager::ShaderManagerOpenGL>(this->shader_manager)
		);

		ManagerLocator::render_manager = dynamic_cast<render_manager::IRenderManager*>(this->render_manager);

		this->OnInit();

		this->event_manager->ConsumeEventBuffer(event_manager::EventType::kWindowCreated);

		// Setup Dear ImGui context
		/*IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_None;*/

		/*auto window = static_cast<GLFWwindow*>(this->window_manager->GetWindow());

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 450");*/

		this->is_running_ = true;
		EE_INFO("Application is now running");

		std::chrono::high_resolution_clock timer;
		using ms = std::chrono::duration<float, std::milli>;

		auto start = timer.now();
		auto stop = timer.now();
		float deltaTime = 0;

		while (this->is_running_) {

			this->event_manager->ConsumeEventBuffer(event_manager::EventType::kEnvironmentUpdate);

			deltaTime = std::chrono::duration_cast<ms>(stop - start).count();
			start = timer.now();

			this->input_manager->PollEvents();
			this->event_manager->ConsumeEventBuffer(event_manager::EventType::kKeyboard);
			this->world->Update(deltaTime);

			/*ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			static bool show = true;
			ImGui::ShowDemoWindow(&show);
			ImGui::Render();*/

			this->event_manager->Dispatch(event_manager::Event(event_manager::EventType::kPreRender));
			this->event_manager->Dispatch(event_manager::Event(event_manager::EventType::kRender));

			// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			this->event_manager->Dispatch(event_manager::Event(event_manager::EventType::kPostRender));


			event_manager::Event event = event_manager::Event();
			event.event_type = event_manager::EventType::kGlobalTick;
			this->event_manager->Dispatch(event);

			stop = timer.now();
		}

		this->window_manager->CloseWindow();
	}

	std::future<void> Application::RunAsync() {
		return std::async([this]() -> void {
			this->Run();
			});
	}

	std::string Application::GetEngineDirectory() {
		return std::experimental::filesystem::current_path().remove_filename().u8string();
	}

	void Application::InitializeDefaultSystems() {
		auto render_system = new render_manager::RenderSystem(this->event_manager);
		world->AddSystem<ecs::component::MeshComponent, ecs::component::TransformComponent>(render_system);

		auto ui_render_system = new ui::UIRenderSystem(this->ui_render_manager);
		world->AddSystem<>(ui_render_system);
	}

	void Application::Close() {
		this->is_running_ = false;
	}

}