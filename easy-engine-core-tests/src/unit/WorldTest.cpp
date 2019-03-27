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
	int x, y = 25;
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

	// TODO should be created on the fly in world if given ComponentManager does not exist yet
	auto component_manager = std::unique_ptr<component_manager::ComponentManager>(new component_manager::ComponentManager());

	world->AddComponentManager<TestComponent>(std::move(component_manager));
	world->AddComponent<TestComponent>(entity.entity, std::unique_ptr<TestComponent>(new TestComponent()));

	BOOST_CHECK_EQUAL(entity.world, world);
}


BOOST_AUTO_TEST_SUITE_END()