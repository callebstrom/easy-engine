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
			transform->Rotation(0.01, 0, 1, 0);
		}
	}
};

class DynamicSceneApplication : public Application {
public:
	DynamicSceneApplication() {

		world->AddSystem<ecs::component::MeshComponent, ecs::component::TransformComponent>(new RotationSystem);

		resource::Mesh* mesh = this->resource_manager_3d->LoadObj("..\\easy-engine-core\\res\\basic_sword_low_poly.obj");
		ecs::component::MeshComponent mesh_component;
		mesh_component.mesh = mesh;

		ecs::component::TransformComponent transform_component;

		auto sword = this->world->CreateEntity();

		this->world->AddComponent<ecs::component::MeshComponent>(sword.entity, mesh_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sword.entity, transform_component);
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