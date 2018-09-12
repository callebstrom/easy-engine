#pragma once

#include <RenderManager.h>
#include <WindowManager.h>
#include <InputManager.h>

#ifndef MANAGER_LOCATOR_H

class easy_engine::render_manager::RenderManager;

class ManagerLocator {
	public:
		static easy_engine::render_manager::RenderManager* render_manager;
		static easy_engine::window_manager::WindowManager* ManagerLocator::window_manager;
		static easy_engine::input_manager::InputManager* ManagerLocator::input_manager;
};

#endif !MANAGER_LOCATOR_H