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
#include <boost/config/user.hpp>

using easy_engine::configuration::WindowConfiguration_t;
using easy_engine::configuration::WindowConfigurationParams;
using easy_engine::render_manager::RenderManagerOpenGL;
using easy_engine::render_manager::RenderManager;
using easy_engine::window_manager::WindowManager;
using easy_engine::window_manager::WindowManagerGLFW;
using easy_engine::configuration::RenderConfiguration_t;
using easy_engine::configuration::RenderConfigurationParams;
using easy_engine::input_manager::InputManager;
using easy_engine::scene_manager::SceneManager3D;
using easy_engine::input_manager::InputManager;
using easy_engine::resource_manager::ResourceManager3D;
using easy_engine::renderable::Renderable3D;


int main() {

	ManagerLocator::input_manager = new InputManager();

	ManagerLocator::window_manager = dynamic_cast<WindowManager*>(new WindowManagerGLFW());
	WindowConfiguration_t* window_configuration = new WindowConfiguration_t();
	window_configuration->Set(WindowConfigurationParams::WIDTH, "1280");
	window_configuration->Set(WindowConfigurationParams::HEIGHT, "720");
	ManagerLocator::window_manager->CreateWindow(window_configuration);

	RenderConfiguration_t* render_configuration = new RenderConfiguration_t();
	render_configuration->Set(RenderConfigurationParams::RESOLUTION_X, "1280");
	render_configuration->Set(RenderConfigurationParams::RESOLUTION_Y, "720");
	render_configuration->Set(RenderConfigurationParams::ANTIALIASING, "8");
	render_configuration->Set(RenderConfigurationParams::VERTEX_SHADER_SOURCE_LOCATION, "..\\..\\..\\easy-engine-core\\src\\shaders\\vertex_shader.glsl");
	render_configuration->Set(RenderConfigurationParams::FRAGMENT_SHADER_SOURCE_LOCATION, "..\\..\\..\\easy-engine-core\\src\\shaders\\fragment_shader.glsl");
	ManagerLocator::render_manager = dynamic_cast<RenderManager*>(new RenderManagerOpenGL(render_configuration));

	SceneManager3D* sm3 = new SceneManager3D();
	ResourceManager3D* rm3d = new ResourceManager3D();

	Renderable3D* ptr = rm3d->LoadObj("..\\..\\..\\easy-engine-core\\res\\basic_sword_low_poly.obj");

	sm3->CreateScene("main");
	sm3->Add(ptr, "main");
	sm3->RenderScene();
}