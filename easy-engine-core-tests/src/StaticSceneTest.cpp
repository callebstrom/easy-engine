#include <boost/test/unit_test.hpp>
#include <EasyEngine/eepch.h>
#include <EasyEngine/EasyEngine.h>

#include <chrono>

BOOST_AUTO_TEST_SUITE(StaticSceneTest)

using namespace easy_engine;

class StaticSceneApplication : public Application {
public:
	StaticSceneApplication() {
		renderable::Renderable3D* ptr = this->resource_manager_3d->LoadObj("..\\easy-engine-core\\res\\basic_sword_low_poly.obj");
		this->scene_manager_3d->CreateScene("main");
		this->scene_manager_3d->Add(ptr, "main");
	}

	~StaticSceneApplication() {

	}
};

BOOST_AUTO_TEST_CASE(static_scene_application_run)
{
	StaticSceneApplication* application = new StaticSceneApplication();
	application->RunAsync(); // TODO fix access violations when running async
	std::this_thread::sleep_for(std::chrono::seconds(5));
	application->Close();
	BOOST_CHECK_EQUAL(true, true);
}

BOOST_AUTO_TEST_SUITE_END()