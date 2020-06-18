#pragma once

namespace Atlas
{

	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return rendererAPI; }
	private:
		static RendererAPI rendererAPI;
	};
}