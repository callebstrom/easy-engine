#include <EasyEngine/eepch.h>
#include <boost/test/unit_test.hpp>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(PlayerTest)

using namespace easy_engine;

using input_manager::Key;
using input_manager::Action;
using input_manager::Modifier;

class PlayerSystem : public ecs::ISystem, public event_manager::IObserver
{
public:
	PlayerSystem()
	{
		ManagerLocator::event_manager->Subscribe(
			event_manager::EventType::Keyboard,
			this
		);
	}

	void OnEvent(event_manager::Event event)
	{
		event_buffer_.push_back(event);
	}

	void Update(float dt) override
	{
		for (auto event_ : this->event_buffer_) {
			auto event = reinterpret_cast<input_manager::KeyboardEvent*>(event_.data);
			if (event->action == Action::kPressed)
			{
				for (auto entity : this->entities_) {
					auto transform = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

					switch (event->key) {
					case Key::kW:
						transform->TranslationAdd(0, 0, -0.01 * dt);
						break;
					case Key::kS:
						transform->TranslationAdd(0, 0, 0.01 * dt);
						break;
					case Key::kA:
						transform->TranslationAdd(-0.01 * dt, 0, 0);
						break;
					case Key::kD:
						transform->TranslationAdd(0.01 * dt, 0, 0);
						break;
					case Key::kR:
						auto rotation_direction = event->modifiers == Modifier::kControl ? -1 : 1;
						transform->RotationAdd(rotation_direction * 0.01 * dt);
						break;
					}
				}
			}
		}

		// Clear buffer after processing all events
		event_buffer_.clear();
	}
private:
	std::vector<event_manager::Event> event_buffer_;

};

class PlayerApplication : public Application {
public:
	PlayerApplication() {

		world->AddSystem<ecs::component::MeshComponent, ecs::component::TransformComponent>(new PlayerSystem);

		ecs::component::MeshComponent mesh_component;
		ecs::component::TextureComponent texture_component;
		ecs::component::MaterialComponent material_component;
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\sylvana\\sylvana.fbx", mesh_component, texture_component, material_component);

		ecs::component::TransformComponent transform_component;
		transform_component.Scale(0.1, 0.1, 0.1);
		transform_component.TranslationAdd(0, -15, -20);
		auto sylvana = this->world->CreateEntity();

		this->world->AddComponent<ecs::component::MeshComponent>(sylvana, mesh_component);
		this->world->AddComponent<ecs::component::TextureComponent>(sylvana, texture_component);
		this->world->AddComponent<ecs::component::MaterialComponent>(sylvana, material_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sylvana, transform_component);

		resource::Environment environment;
		resource::PointLight point_light;
		point_light.position = Eigen::Vector3f(0.f, 1.f, 5.f);
		point_light.strength = 10.f;

		resource::PointLight point_light2;
		point_light.position = Eigen::Vector3f(-5.f, 0.f, 5.f);
		point_light.strength = 75.f;

		environment.AddLight(point_light);
		environment.AddLight(point_light2);

		world->SetupEnvironment(environment);
	}

	~PlayerApplication() {

	}
};

BOOST_AUTO_TEST_CASE(player_application_run)
{
	PlayerApplication* application = new PlayerApplication();
	application->Run();
	// std::this_thread::sleep_for(std::chrono::seconds(30));
	// application->Close();
	BOOST_CHECK_EQUAL("player_test", "player_test");
}

BOOST_AUTO_TEST_SUITE_END()