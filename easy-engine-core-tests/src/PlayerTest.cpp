#include <EasyEngine/eepch.h>
#include <boost/test/unit_test.hpp>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(PlayerTest)

using namespace easy_engine;

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
			if (event->action == EE_KEY_ACTION_PRESSED)
			{
				for (auto entity : this->entities_) {
					auto transform = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

					switch (event->key) {
					case EE_KEY_W:
						transform->TranslationAdd(0, 0, -0.01 * dt);
						break;
					case EE_KEY_S:
						transform->TranslationAdd(0, 0, 0.01 * dt);
						break;
					case EE_KEY_A:
						transform->TranslationAdd(-0.01 * dt, 0, 0);
						break;
					case EE_KEY_D:
						transform->TranslationAdd(0.01 * dt, 0, 0);
						break;
					case EE_KEY_R:
						auto rotation_direction = event->modifiers == EE_MOD_CONTROL ? -1 : 1;
						transform->RotationAdd(rotation_direction * 0.01 * dt, 0, 1, 0);
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
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\nanosuit.fbx", mesh_component);

		ecs::component::TransformComponent transform_component;
		transform_component.TranslationAdd(0, -7, -30);

		auto sword = this->world->CreateEntity();

		this->world->AddComponent<ecs::component::MeshComponent>(sword.entity, mesh_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sword.entity, transform_component);
	}

	~PlayerApplication() {

	}
};

BOOST_AUTO_TEST_CASE(player_application_run)
{
	PlayerApplication* application = new PlayerApplication();
	std::future<void> asyncApplication = application->RunAsync();
	std::this_thread::sleep_for(std::chrono::seconds(15));
	application->Close();
	BOOST_CHECK_EQUAL("player_test", "player_test");
}

BOOST_AUTO_TEST_SUITE_END()