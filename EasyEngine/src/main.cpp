#include <iostream>

#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>
#include <SceneManagerOpenGL.h>
#include <Renderable.h>
#include <WindowConfiguration.h>
#include <ManagerLocator.h>
#include <RenderConfiguration.h>

using namespace easy_engine;

using easy_engine::configuration::WindowConfiguration_t;
using easy_engine::configuration::WindowConfigurationParams;
using easy_engine::render_manager::RenderManagerOpenGL;
using easy_engine::render_manager::RenderManager;
using easy_engine::configuration::RenderConfiguration_t;
using easy_engine::configuration::RenderConfigurationParams;


int main() {

	RenderConfiguration_t* render_configuration = new RenderConfiguration_t();
	render_configuration->Set(RenderConfigurationParams::RESOLUTION_X, "1280");
	render_configuration->Set(RenderConfigurationParams::RESOLUTION_Y, "720");
	render_configuration->Set(RenderConfigurationParams::ANTIALIASING, "8");
	render_configuration->Set(RenderConfigurationParams::VERTEX_SHADER_SOURCE_LOCATION, "D:\\Dropbox\\dev\\EasyEngine\\EasyEngine\\src\\shaders\\vertex_shader.glsl");
	render_configuration->Set(RenderConfigurationParams::FRAGMENT_SHADER_SOURCE_LOCATION, "D:\\Dropbox\\dev\\EasyEngine\\EasyEngine\\src\\shaders\\fragment_shader.glsl");

	ManagerLocator::render_manager = dynamic_cast<RenderManager*>(new RenderManagerOpenGL(render_configuration));

	WindowConfiguration_t* window_configuration = new WindowConfiguration_t();
	window_configuration->Set(WindowConfigurationParams::WIDTH, "1280");
	window_configuration->Set(WindowConfigurationParams::HEIGHT, "720");

	scene_manager::SceneManagerOpenGL* sm3 = new scene_manager::SceneManagerOpenGL();
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D("C:\\test\\");

	renderable::Renderable3D* ptr = rm3d->LoadObj("susanne_hi_poly.obj");

	sm3->CreateScene("main");
	sm3->Add(ptr, "main");
	sm3->RenderScene();
}