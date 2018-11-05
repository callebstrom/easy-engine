#pragma once

#include <EasyEngine/render_manager/RenderManagerOpenGL.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/configuration/WindowConfiguration.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/resource_manager/ResourceManager3D.h>
#include <EasyEngine/scene_manager/SceneManager3D.h>
#include <EasyEngine/renderable/Renderable.h>
#include <EasyEngine/ManagerLocator.h>
#include <boost/config/user.hpp>

#include <EasyEngine/window_manager/WindowManagerGLFW.h>

namespace easy_engine {
	class EASY_ENGINE_API Application {
		public:
			Application();
			virtual ~Application();
			void Run();
	};

	Application* CreateApplication();
}