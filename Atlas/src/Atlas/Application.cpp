#include "atlaspch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Atlas/Log.h"

#include "glad/glad.h"


#include "Atlas/Input.h"

#include "glm/glm.hpp"

namespace Atlas
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

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

			// update layers
			for (Layer* layer : layerStack)
				layer->OnUpdate();

			// render ImGui
			m_ImGuiLayer->Begin();
			for (Layer* layer : layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

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


		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}
}