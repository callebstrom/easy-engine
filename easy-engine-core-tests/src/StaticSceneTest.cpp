#include <EasyEngine/eepch.h>
#include <boost/test/unit_test.hpp>
#include <EasyEngine/EasyEngine.h>

#include <chrono>

BOOST_AUTO_TEST_SUITE(StaticSceneTest)

using namespace easy_engine;

class StaticSceneApplication : public Application {
public:
	StaticSceneApplication() {
		resource::Mesh* ptr = this->resource_manager_3d->LoadObj("..\\easy-engine-core\\res\\basic_sword_low_poly.obj");
		this->scene_manager_3d->CreateScene("main");
		this->scene_manager_3d->Add(ptr, "main");
	}

	~StaticSceneApplication() {

	}
};

BOOST_AUTO_TEST_CASE(static_scene_application_run)
{
	StaticSceneApplication* application = new StaticSceneApplication();
	std::future<void> asyncApplication = application->RunAsync();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	application->Close();
	BOOST_CHECK_EQUAL("static_scene_test", "static_scene_test");
}

BOOST_AUTO_TEST_SUITE_END()