#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>

using namespace easy_engine;

int main() {
	configuration::RenderConfiguration* rc = new configuration::RenderConfiguration();
	render_manager::RenderManagerOpenGL* rmol = new render_manager::RenderManagerOpenGL(rc);
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D("C:\\test\\");
	renderable::IRenderable3D<float*>* ptr = rm3d->LoadObj("box.obj");

	rmol->Render();
}