#include "PCH.h"
#include "Application.h"

#include "Kaju/Events/ApplicationEvent.h"
#include "Kaju/Log.h"

KJ::Application::Application()
{ 
	m_window = std::unique_ptr<Window>(Window::Create());
	m_window->SetEventCallback(std::bind(&KJ::Application::OnEvent, this, std::placeholders::_1));
}

KJ::Application::~Application()
{

}

void KJ::Application::Run()
{
	while (m_running)
	{
		m_window->OnUpdate();
	}
}

void KJ::Application::OnEvent(Event& event)
{
	KJ_CORE_TRACE(event.ToString());
}
