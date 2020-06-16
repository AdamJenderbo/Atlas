#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Atlas/Log.h"

namespace Atlas
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		LOG_WARNING(e.ToString());
		while (true);
	}
}