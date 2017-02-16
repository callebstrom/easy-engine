#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <ResourceManager3D.h>

using namespace easy_engine;

int main() {
	configuration::RenderConfiguration* rc = new configuration::RenderConfiguration();
	render_manager::RenderManagerOpenGL* rmol = new render_manager::RenderManagerOpenGL(rc);
	rmol->Render();
	resource_manager::ResourceManager3D* rm3d = new resource_manager::ResourceManager3D("C:/test");
	rm3d->LoadObj("box.obj");
}