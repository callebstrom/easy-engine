#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H
#pragma once

#include <EasyEngine/Application.h>

extern easy_engine::Application* easy_engine::CreateApplication();

#ifndef NO_ENTRYPOINT
int main(int argc, char** argv) {
	auto app = easy_engine::CreateApplication();
	app->Run();
	delete app;
}
#endif

#endif // !ENTRY_POINT_H