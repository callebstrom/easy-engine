#include <EasyEngine/eepch.h>
#include <EasyEngine/ManagerLocator.h>

easy_engine::render_manager::IRenderManager* ManagerLocator::render_manager = NULL;
easy_engine::event_manager::EventManager* ManagerLocator::event_manager = NULL;
easy_engine::resource_manager::ResourceManager* ManagerLocator::resource_manager = NULL;