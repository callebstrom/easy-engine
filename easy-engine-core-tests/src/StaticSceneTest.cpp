#include <EasyEngine/eepch.h>
#include <boost/test/unit_test.hpp>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(StaticSceneTest)

using namespace easy_engine;

class StaticSceneApplication : public Application {
public:
	StaticSceneApplication() {
		ecs::component::MeshComponent mesh_component;
		ecs::component::TransformComponent transform_component;
		transform_component.RotationAdd(0.5, 0, 1, 0);
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\cube.fbx", mesh_component);

		auto sword = this->world->CreateEntity();
		this->world->AddComponent<ecs::component::MeshComponent>(sword.entity, mesh_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sword.entity, transform_component);
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