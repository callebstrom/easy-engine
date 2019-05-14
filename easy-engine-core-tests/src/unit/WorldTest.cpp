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

struct TestComponent : public component::IComponent {
	int x = 10,
		y = 25;
};

class TestSystem : public ISystem {
	void Update(float dt) override
	{

	};
};

BOOST_AUTO_TEST_CASE(get_components_by_type)
{

	auto world = new world::World();
	auto testSystem = std::make_unique<TestSystem>();
	world->AddSystem(std::move(testSystem));

	auto entity = world->CreateEntity();

	world->AddComponent<TestComponent>(entity.entity, std::move(std::unique_ptr<TestComponent>(new TestComponent())));

	world->GetComponentsByType<TestComponent>();
}


BOOST_AUTO_TEST_SUITE_END()