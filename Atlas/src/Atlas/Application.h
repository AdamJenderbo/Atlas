#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Atlas/Layer.h"
#include "LayerStack.h"

#include "Atlas/ImGui/ImGuiLayer.h"

#include "Atlas/Renderer/Shader.h"
#include "Atlas/Renderer/Buffer.h"
#include "Atlas/Renderer/VertexArray.h"

#include "Atlas/Renderer/OrthographicCamera.h"

#include "Atlas/Timestep.h"
#include "Atlas/ImGui/ImGuiLayer.h"



namespace Atlas
{
	class ATLAS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);
		inline static Application& Get()
		{
			return *s_Instance;
		}

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		
		ImGuiLayer* m_ImGuiLayer;
		bool isRunning = true;
		LayerStack layerStack;

		float m_LastFrameTime = 0.0f;
		static Application* s_Instance;

	};

	Application* CreateApplication();
}