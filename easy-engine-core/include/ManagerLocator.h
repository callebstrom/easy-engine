#ifndef MANAGER_LOCATOR_H
#define MANAGER_LOCATOR_H
#pragma once

#include <RenderManager.h>
#include <WindowManager.h>
#include <InputManager.h>

class easy_engine::render_manager::RenderManager;

class DLLEXPORT ManagerLocator {
public:
	static easy_engine::render_manager::RenderManager* render_manager;
	static easy_engine::window_manager::WindowManager* window_manager;
	static easy_engine::input_manager::InputManager* input_manager;
};

#endif // !MANAGER_LOCATOR_H
