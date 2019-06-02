#include <boost/test/unit_test.hpp>

#include <EasyEngine/eepch.h>
#include <EasyEngine/EasyEngine.h>

BOOST_AUTO_TEST_SUITE(WorldTest)

using namespace easy_engine;
BOOST_AUTO_TEST_CASE(load_file)
{
	auto resource_manager = resource_manager::ResourceManager3D();

	ecs::component::MeshComponent mesh_component;

	resource_manager.Load("..\\easy-engine-core\\res\\player_low_poly.obj", mesh_component);
}

BOOST_AUTO_TEST_SUITE_END()