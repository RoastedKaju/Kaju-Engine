#include <Kaju.h>

class ExampleLayer : public KJ::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//KJ_INFO("ExampleLayer::Update");
	}

	void OnEvent(KJ::Event& event) override
	{
		KJ_TRACE("{0}", event.ToString());
	}

};

class Sandbox : public KJ::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new KJ::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

KJ::Application* KJ::CreateApplication()
{
	return new Sandbox();
}