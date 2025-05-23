#include "PCH.h"
#include "Application.h"

#include "Kaju/Events/ApplicationEvent.h"
#include "Kaju/Log.h"

KJ::Application::Application()
{ 
	m_window = std::unique_ptr<Window>(Window::Create());
	m_window->SetEventCallback(BIND_EVENT(&KJ::Application::OnEvent, this));
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
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(&KJ::Application::OnWindowClose, this));

	KJ_CORE_TRACE(event.ToString());
}

bool KJ::Application::OnWindowClose(WindowCloseEvent& event)
{
	m_running = false;
	return true;
}
