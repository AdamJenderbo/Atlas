#include <Atlas.h>

class ExampleLayer : public Atlas::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Atlas::Input::IsKeyPressed(KEY_TAB))
			LOG_INFO("Tab key is pressed (poll)!");
	}

	void OnEvent(Atlas::Event& event) override
	{
		if (event.GetEventType() == Atlas::EventType::KeyPressed)
		{
			Atlas::KeyPressedEvent& e = (Atlas::KeyPressedEvent&)event;
			if (e.GetKeyCode() == KEY_TAB)
				LOG_INFO("Tab key is pressed (event)!");
			LOG_INFO("{0}", (char)e.GetKeyCode());
		}
	}
};


class Sandbox : public Atlas::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Atlas::Application* Atlas::CreateApplication()
{
	return new Sandbox();
}