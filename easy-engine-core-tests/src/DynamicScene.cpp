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
		ecs::component::TextureComponent texture_component;
		ecs::component::MaterialComponent material_component;
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\nanosuit.fbx", mesh_component, texture_component, material_component);

		ecs::component::TransformComponent transform_component;
		transform_component.TranslationAdd(0, 0, -10);
		auto cube = this->world->CreateEntity();

		this->world->AddComponent<ecs::component::MeshComponent>(cube.entity, mesh_component);
		this->world->AddComponent<ecs::component::TransformComponent>(cube.entity, transform_component);
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