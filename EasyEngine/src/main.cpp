#include <iostream>

#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>
#include <SceneManager3D.h>
#include <Renderable.h>
#include <WindowConfiguration.h>
#include <ManagerLocator.h>
#include <RenderConfiguration.h>
#include <WindowManagerGLFW.h>

using namespace easy_engine;

using easy_engine::configuration::WindowConfiguration_t;
using easy_engine::configuration::WindowConfigurationParams;
using easy_engine::render_manager::RenderManagerOpenGL;
using easy_engine::render_manager::RenderManager;
using easy_engine::window_manager::WindowManager;
using easy_engine::window_manager::WindowManagerGLFW;
using easy_engine::configuration::RenderConfiguration_t;
using easy_engine::configuration::RenderConfigurationParams;

int main() {

	ManagerLocator::input_manager = new input_manager::InputManager();

	ManagerLocator::window_manager = dynamic_cast<WindowManager*>(new WindowManagerGLFW());
	WindowConfiguration_t* window_configuration = new WindowConfiguration_t();
	window_configuration->Set(WindowConfigurationParams::WIDTH, "1920");
	window_configuration->Set(WindowConfigurationParams::HEIGHT, "1080");
	ManagerLocator::window_manager->CreateWindow(window_configuration);

	RenderConfiguration_t* render_configuration = new RenderConfiguration_t();
	render_configuration->Set(RenderConfigurationParams::RESOLUTION_X, "1920");
	render_configuration->Set(RenderConfigurationParams::RESOLUTION_Y, "1080");
	render_configuration->Set(RenderConfigurationParams::ANTIALIASING, "8");
	render_configuration->Set(RenderConfigurationParams::VERTEX_SHADER_SOURCE_LOCATION, "..\\..\\EasyEngine\\EasyEngine\\src\\shaders\\vertex_shader.glsl");
	render_configuration->Set(RenderConfigurationParams::FRAGMENT_SHADER_SOURCE_LOCATION, "..\\..\\EasyEngine\\EasyEngine\\src\\shaders\\fragment_shader.glsl");
	ManagerLocator::render_manager = dynamic_cast<RenderManager*>(new RenderManagerOpenGL(render_configuration));

	scene_manager::SceneManager3D* sm3 = new scene_manager::SceneManager3D();
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D();

	renderable::Renderable3D* ptr = rm3d->LoadObj("..\\..\\EasyEngine\\EasyEngine\\res\\basic_sword_low_poly.obj");

	sm3->CreateScene("main");
	sm3->Add(ptr, "main");
	sm3->RenderScene();
}