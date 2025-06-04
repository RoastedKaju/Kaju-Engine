#include "PCH.h"
#include "Application.h"

#include "Kaju/Events/ApplicationEvent.h"
#include "Kaju/Log.h"

KJ::Application* KJ::Application::s_instance = nullptr;

KJ::Application::Application()
{
	KJ_CORE_ASSERT(!m_instance, "Application already exists");
	s_instance = this;

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

		// Update layers inside layer stack
		for (auto layer : m_layerStack)
		{
			layer->OnUpdate();
		}
	}
}

void KJ::Application::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(&KJ::Application::OnWindowClose, this));

	KJ_CORE_TRACE(event.ToString());

	// Poll the layer events in reverse order so the top most layer gets the event first
	for (auto itr = m_layerStack.end(); itr != m_layerStack.begin(); )
	{
		(*--itr)->OnEvent(event);
		// if handled then don't send further down the layers
		if (event.m_Handled)
		{
			break;
		}
	}
}

void KJ::Application::PushLayer(Layer* layer)
{
	m_layerStack.PushLayer(layer);
	layer->OnAttach();
}

void KJ::Application::PushOverlay(Layer* overlay)
{
	m_layerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

bool KJ::Application::OnWindowClose(WindowCloseEvent& event)
{
	m_running = false;
	return true;
}
