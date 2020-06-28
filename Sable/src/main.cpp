#include <iostream>
#include "Shake.h"

class BaseLayer : public Shake::Layer
{
public:
	BaseLayer() : Layer("Base")
	{
		
	}

	void OnUpdate() override
	{
		//SE_INFO("BaseLayer::OnUpdate");
	}

	void OnEvent(Shake::Event& event) override
	{
		//SE_TRACE("{0}", event.ToString());
	}
};

class Sable : public Shake::Application
{
public:
	Sable(const std::string& applicationName) : Application(applicationName)
	{
		PushLayer(new BaseLayer());
		PushLayer(new Shake::ImGuiLayer());
	}

	~Sable()
	{
		
	}
};

Shake::Application* Shake::CreateApplication()
{
	return new Sable("Sable");
}
