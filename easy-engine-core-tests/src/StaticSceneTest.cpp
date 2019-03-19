#include <EasyEngine/eepch.h>
#include <EasyEngine/EasyEngine.h>

using namespace easy_engine;


class StaticSceneTest : public Application {
	public:
		StaticSceneTest() {
			/*renderable::Renderable3D* ptr = this->resource_manager_3d->LoadObj("..\\easy-engine-core\\res\\basic_sword_low_poly.obj");
			this->scene_manager_3d->CreateScene("main");
			this->scene_manager_3d->Add(ptr, "main");*/
		}

		~StaticSceneTest() {

		}
};


Application* easy_engine::CreateApplication() {
	Application* application = new StaticSceneTest();
	return application;
}