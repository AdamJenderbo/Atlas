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

		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;

		std::shared_ptr<Shader> blueShader;
		std::shared_ptr<VertexArray> squareVA;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}