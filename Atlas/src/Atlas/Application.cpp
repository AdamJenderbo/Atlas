#include "atlaspch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Atlas/Log.h"
#include "GLFW/glfw3.h"
namespace Atlas
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (isRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}