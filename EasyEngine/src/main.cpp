#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>
#include <SceneManager3DOpenGL.h>
#include <Renderable.h>

using namespace easy_engine;

int main() {
	scene_manager::SceneManager3DOpenGL* sm3 = new scene_manager::SceneManager3DOpenGL();

	configuration::RenderConfiguration* rc = new configuration::RenderConfiguration();
	render_manager::RenderManagerOpenGL* rmol = new render_manager::RenderManagerOpenGL(rc);
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D("C:\\test\\");
	renderable::IRenderable3D<float*>* ptr = rm3d->LoadObj("box.obj");

	rmol->Render();
}