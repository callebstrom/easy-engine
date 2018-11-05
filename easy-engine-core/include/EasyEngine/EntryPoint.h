#pragma once

#include <EasyEngine/Application.h>

extern easy_engine::Application* easy_engine::CreateApplication();

int main(int argc, char** argv) {
	auto app = easy_engine::CreateApplication();
	app->Run();
	delete app;
}