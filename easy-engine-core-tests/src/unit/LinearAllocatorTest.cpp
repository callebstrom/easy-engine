#include <boost/test/unit_test.hpp>

#include <EasyEngine/eepch.h>
#include <EasyEngine/memory/LinearAllocator.h>

BOOST_AUTO_TEST_SUITE(WorldTest)

struct GameObject
{
	GameObject(int value)
		: value(value) {};

	int value;
};

using namespace easy_engine;
BOOST_AUTO_TEST_CASE(linear_allocator_realloc)
{
	// Initial size of 1
	memory::LinearAllocator<GameObject> allocator(1);

	GameObject game_object1(12);
	GameObject game_object2(43);
	GameObject game_object3(52);

	auto offset1 = allocator.Allocate(&game_object1);
	auto offset2 = allocator.Allocate(&game_object2);
	auto offset3 = allocator.Allocate(&game_object3);

	BOOST_CHECK_EQUAL((allocator.buffer + offset1)->value, game_object1.value);
	BOOST_CHECK_EQUAL((allocator.buffer + offset2)->value, game_object2.value);
	BOOST_CHECK_EQUAL((allocator.buffer + offset3)->value, game_object3.value);

}

BOOST_AUTO_TEST_SUITE_END()