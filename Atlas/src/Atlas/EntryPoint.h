#pragma once
#include "Application.h"

#ifdef ATLAS_PLATFORM_WINDOWS

extern Atlas::Application* Atlas::CreateApplication();

int main(int argc, char** argv)
{
	Atlas::Log::Init();
	LOG_INFO("Welcome to Atlas Engine!");

	auto app = Atlas::CreateApplication();
	app->Run();
	delete app;
}
#endif
