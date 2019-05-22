#include <boost/test/unit_test.hpp>

#include <EasyEngine/eepch.h>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(WorldTest)

using namespace easy_engine;
BOOST_AUTO_TEST_CASE(create_entity_id_sequence)
{
	auto world = new world::World();
	auto entityHandle = world->CreateEntity();

	BOOST_CHECK_EQUAL(entityHandle.world, world);
}

struct TransformComponent : public component::Component {
	int x = 10,
		y = 25;
};

struct VelocityComponent : public component::Component {
	int velocity = 33;
};

class TestSystem : public ISystem {
	void Update(float dt) override
	{
		auto test_component = this->world->GetComponentForEntity<TransformComponent>(this->entities_[0]);
		auto velocity_component = this->world->GetComponentForEntity<VelocityComponent>(this->entities_[0]);

		test_component->x += velocity_component->velocity;
	};
};
BOOST_AUTO_TEST_CASE(should_register_eligable_entity_for_multi_component_system)
{
	auto world = new world::World();
	world->AddSystem<TransformComponent, VelocityComponent>(new TestSystem);

	auto entity_handle1 = world->CreateEntity();
	auto entity_handle2 = world->CreateEntity();

	TransformComponent transform_component;
	VelocityComponent velocity_component;
	TransformComponent transform_component2;

	// Only entity1 should be handle by TestSystem
	world->AddComponent<TransformComponent>(entity_handle1.entity, transform_component);
	world->AddComponent<VelocityComponent>(entity_handle1.entity, velocity_component);
	world->AddComponent<TransformComponent>(entity_handle2.entity, transform_component2);

	// Simulate app tick with 1ms delta time
	world->Update(1.0f);

	// The transform of entity_handle2 should be untouched
	BOOST_CHECK_EQUAL(world->GetComponentForEntity<TransformComponent>(entity_handle2.entity)->x, 10);

	// entity_handle1 should have velocity added as its fulfills the component requirements of TestSystem
	BOOST_CHECK_EQUAL(world->GetComponentForEntity<TransformComponent>(entity_handle1.entity)->x, 10 + 33);
}


BOOST_AUTO_TEST_SUITE_END()