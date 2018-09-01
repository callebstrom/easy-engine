#include <iostream>

#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>
#include <SceneManagerOpenGL.h>
#include <Renderable.h>
#include <SceneConfiguration.h>

using namespace easy_engine;

using easy_engine::configuration::SceneConfiguration_t;
using easy_engine::configuration::SceneConfigurationParams;

int main() {

	SceneConfiguration_t* scene_configuration = new SceneConfiguration_t();
	scene_configuration->Set(SceneConfigurationParams::SCENE_RESOLUTION_X, "640");
	scene_configuration->Set(SceneConfigurationParams::SCENE_RESOLUTION_Y, "600");

	scene_manager::SceneManagerOpenGL* sm3 = new scene_manager::SceneManagerOpenGL(scene_configuration);
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D("C:\\test\\");

	renderable::Renderable3D* ptr = rm3d->LoadObj("triangle.obj");

	sm3->CreateScene("main");
	sm3->Add(ptr, "main");
	sm3->RenderScene();
}