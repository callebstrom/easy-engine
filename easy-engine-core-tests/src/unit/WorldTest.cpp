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
	auto test_system = std::make_unique<TestSystem>();
	world->AddSystem(std::move(test_system));

	auto entity = world->CreateEntity();

	std::shared_ptr<TestComponent> test_component(new TestComponent);
	world->AddComponent<TestComponent>(entity.entity, test_component);

	auto test_components = world->GetComponentsByType<TestComponent>();
	auto key = std::type_index(typeid(TestComponent));

	BOOST_CHECK_EQUAL(test_components[key].at(0)->x, 10);
	BOOST_CHECK_EQUAL(test_components[key].at(0)->y, 25);
}


BOOST_AUTO_TEST_SUITE_END()