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
#include <EasyEngine/renderable/Renderable.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/window_manager/WindowManagerGLFW.h>

namespace easy_engine {
	class EASY_ENGINE_API Application {
		public:
			Application();
			virtual ~Application();
			void Run();
		protected:
			scene_manager::SceneManager3D* scene_manager_3d;
			resource_manager::ResourceManager3D* resource_manager_3d;
			input_manager::InputManager* input_manager;
			window_manager::WindowManagerGLFW* window_manager;
			render_manager::RenderManagerOpenGL* render_manager;
		private:
			bool is_running_ = false;
	};

	Application* CreateApplication();
}

#endif // !APPLICATION_H