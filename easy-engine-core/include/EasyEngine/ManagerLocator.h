#ifndef MANAGER_LOCATOR_H
#define MANAGER_LOCATOR_H
#pragma once

#include <EasyEngine/render_manager/RenderManager.h>
#include <EasyEngine/window_manager/WindowManager.h>
#include <EasyEngine/input_manager/InputManager.h>

class easy_engine::render_manager::RenderManager;

class EASY_ENGINE_API ManagerLocator {
public:
	static easy_engine::render_manager::RenderManager* render_manager;
	static easy_engine::window_manager::WindowManager* window_manager;
	static easy_engine::input_manager::InputManager* input_manager;
};

#endif // !MANAGER_LOCATOR_H
