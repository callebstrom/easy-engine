#include <EasyEngine/eepch.h>
#include <boost/test/unit_test.hpp>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(DynamicSceneTest)

using namespace easy_engine;

class RotationSystem : public ecs::ISystem
{
	void Update(float dt) override
	{
		for (auto entity : this->entities_) {
			auto transform = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);
			transform->RotationAdd(0.01, 0, 1, 0);
		}
	}
};

class DynamicSceneApplication : public Application {
public:
	DynamicSceneApplication() {

		world->AddSystem<ecs::component::MeshComponent, ecs::component::TransformComponent>(new RotationSystem);

		ecs::component::MeshComponent mesh_component;
		ecs::component::MeshComponent mesh_component2;
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\radiator.obj", mesh_component);
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\box_simple.obj", mesh_component2);

		ecs::component::TransformComponent transform_component;
		ecs::component::TransformComponent transform_component2;
		transform_component2.TranslationAdd(0.5, 0, 0);

		auto sword = this->world->CreateEntity();
		auto box = this->world->CreateEntity();

		this->world->AddComponent<ecs::component::MeshComponent>(sword.entity, mesh_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sword.entity, transform_component);

		this->world->AddComponent<ecs::component::MeshComponent>(box.entity, mesh_component2);
		this->world->AddComponent<ecs::component::TransformComponent>(box.entity, transform_component2);
	}

	~DynamicSceneApplication() {

	}
};

BOOST_AUTO_TEST_CASE(dynamic_scene_application_run)
{
	DynamicSceneApplication* application = new DynamicSceneApplication();
	std::future<void> asyncApplication = application->RunAsync();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	application->Close();
	BOOST_CHECK_EQUAL("dynamic_scene_test", "dynamic_scene_test");
}

BOOST_AUTO_TEST_SUITE_END()