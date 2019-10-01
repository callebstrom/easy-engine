#ifndef MANAGER_LOCATOR_H
#define MANAGER_LOCATOR_H
#pragma once

#include <EasyEngine/render_manager/RenderManager.h>
#include <EasyEngine/window_manager/IWindowManager.h>
#include <EasyEngine/input_manager/InputManager.h>
#include <EasyEngine/event_manager/EventManager.h>
#include <EasyEngine/resource_manager/ResourceManager.h>

class EASY_ENGINE_API ManagerLocator {
public:
	static easy_engine::render_manager::IRenderManager* render_manager;
	static easy_engine::event_manager::EventManager* event_manager;
	static easy_engine::resource_manager::ResourceManager* resource_manager;
};

#endif // !MANAGER_LOCATOR_H
