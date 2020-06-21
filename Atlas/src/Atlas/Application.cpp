#include "atlaspch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Atlas/Log.h"
#include "Atlas/Renderer/Renderer.h"

#include "Atlas/Input.h"

#include "glm/glm.hpp"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Atlas
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		vertexArray.reset(VertexArray::Create()); // create VAO

		float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		}; // create vertices

		std::shared_ptr<VertexBuffer> vertexBuffer; // create vertex buffer
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices))); // store vertices in vertex buffer
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		}; // create buffer layout
		vertexBuffer->SetLayout(layout); // set buffer layout
		vertexArray->AddVertexBuffer(vertexBuffer); // add vertex buffer to VAO


		uint32_t indices[3] = { 0, 1, 2 }; // create indices
		std::shared_ptr<IndexBuffer> indexBuffer; // create index buffer
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t))); // store indices in index buffer 
		vertexArray->SetIndexBuffer(indexBuffer); // add index buffer to VAO


		squareVA.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform mat4 u_ViewProjection;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
					color = vec4(v_Position * 0.5 + 0.5, 1.0);

			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));


		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
		{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{

				color = vec4(0.2, 0.3, 0.8, 1.0);

			}
		)";

		blueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));


	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (isRunning)
		{
			RenderCommand::SetClearColor({ 0.39f, 0.58f, 0.92f, 1 });
			RenderCommand::Clear();

			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);
			Renderer::Submit(blueShader, squareVA);
			Renderer::Submit(shader, vertexArray);

			Renderer::EndScene();

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