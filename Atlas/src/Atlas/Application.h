#pragma once
#include "Core.h"
#include "Window.h"

namespace Atlas
{
	class __declspec(dllexport) Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool isRunning = true;
	};

	Application* CreateApplication();
}