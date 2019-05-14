#include <EasyEngine/eepch.h>
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <io.h>

#include <fcntl.h>
#include <EasyEngine/ScriptEngine.h>

BOOST_AUTO_TEST_SUITE(ScriptEngineTest)

using namespace easy_engine;

BOOST_AUTO_TEST_CASE(eval_print)
{
	auto script_engine = new script_engine::ScriptEngine();

	auto source = R"(print("Hello World"))";
	script_engine->Eval(source);
}

BOOST_AUTO_TEST_CASE(inherit_application)
{
	auto script_engine = new script_engine::ScriptEngine();
	auto source = R"(print("Hello World"))";
}


BOOST_AUTO_TEST_SUITE_END()