#include <boost/test/unit_test.hpp>

#include <EasyEngine/eepch.h>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(WorldTest)

using namespace easy_engine;
BOOST_AUTO_TEST_CASE(create_entity_id_sequence)
{
	world::World* world = new world::World();
	entity::EntityHandle entityHandle = world->CreateEntity();

	BOOST_CHECK_EQUAL(entityHandle.world, world);
}

BOOST_AUTO_TEST_SUITE_END()