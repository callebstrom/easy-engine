#pragma once

#include <RenderManager.h>

#ifndef MANAGER_LOCATOR_H

class easy_engine::render_manager::RenderManager;

class ManagerLocator {
	public:
		static easy_engine::render_manager::RenderManager* render_manager;
};

#endif !MANAGER_LOCATOR_H