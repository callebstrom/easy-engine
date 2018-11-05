#include <EasyEngine/ManagerLocator.h>

easy_engine::render_manager::RenderManager* ManagerLocator::render_manager = NULL;
easy_engine::window_manager::WindowManager* ManagerLocator::window_manager = NULL;
easy_engine::input_manager::InputManager* ManagerLocator::input_manager = NULL;

