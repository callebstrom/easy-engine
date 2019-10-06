#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once

#include <boost/config/user.hpp>

#include <EasyEngine/render_manager/RenderManagerOpenGL.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/configuration/WindowConfiguration.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/resource_manager/ResourceManager3D.h>
#include <EasyEngine/scene_manager/SceneManager3D.h>
#include <EasyEngine/resource/Renderable.h>
#include <EasyEngine/resource/Environment.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/window_manager/WindowManagerGLFW.h>
#include <EasyEngine/ecs/entity/EntityHandle.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/ecs/component_manager/ComponentManager.h>
#include <EasyEngine/ecs/ISystem.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/input_manager/KeyboardEvent.h>
#include <EasyEngine/shader_manager/IShaderManager.h>
#include <EasyEngine/ui/UIRenderManagerOpenGL.h>

namespace easy_engine {

	class EASY_ENGINE_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
		void Close();
		virtual void OnInit() = 0;
		std::future<void> RunAsync();
		static std::string GetEngineDirectory();
	protected:
		scene_manager::SceneManager3D* scene_manager_3d;
		resource_manager::ResourceManager3D* resource_manager_3d;
		std::shared_ptr<input_manager::InputManager> input_manager;
		std::shared_ptr<window_manager::IWindowManager> window_manager;
		render_manager::IRenderManager* render_manager;
		std::shared_ptr<shader_manager::IShaderManager> shader_manager;
		std::shared_ptr<event_manager::EventManager> event_manager;
		std::shared_ptr<ui::IUIRenderManager> ui_render_manager;
		world::World* world;
	private:
		bool is_running_ = false;
		void InitializeDefaultSystems();
	};

	Application* CreateApplication();

	EASY_ENGINE_EXTERN_TEMPLATE EASY_ENGINE_API int ecs::component::Component::GetComponentFamily<ecs::component::MeshComponent>();
	EASY_ENGINE_EXTERN_TEMPLATE EASY_ENGINE_API int ecs::component::Component::GetComponentFamily<ecs::component::TransformComponent>();
	EASY_ENGINE_EXTERN_TEMPLATE EASY_ENGINE_API int ecs::component::Component::GetComponentFamily<ecs::component::TextureComponent>();
	EASY_ENGINE_EXTERN_TEMPLATE EASY_ENGINE_API int ecs::component::Component::GetComponentFamily<ecs::component::MaterialComponent>();
}


#endif // !APPLICATION_H