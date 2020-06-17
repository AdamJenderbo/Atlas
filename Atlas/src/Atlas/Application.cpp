#include "atlaspch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Atlas/Log.h"

#include "glad/glad.h"

namespace Atlas
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (isRunning)
		{


			glClearColor(0.39f, 0.58f, 0.92f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		LOG_INFO("{0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}
}