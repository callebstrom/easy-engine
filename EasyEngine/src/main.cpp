#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>
#include <SceneManager3DOpenGL.h>
#include <Renderable.h>
#include <iostream>

using namespace easy_engine;

int main() {
	scene_manager::SceneManager3DOpenGL* sm3 = new scene_manager::SceneManager3DOpenGL();
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D("C:\\test\\");

	renderable::Renderable3DOpenGL* ptr = new renderable::Renderable3DOpenGL();
	rm3d->LoadObj("box.obj", *ptr);
	
	sm3->CreateScene("main");
	sm3->Add(ptr, "main");
	sm3->RenderScene();
}