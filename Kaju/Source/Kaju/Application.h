#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Kaju/Window.h"

namespace KJ
{
	class Application
	{
	public:
		KAJU_API Application();
		KAJU_API virtual ~Application();

		KAJU_API void Run();

		KAJU_API void OnEvent(Event& event);

		KAJU_API void PushLayer(Layer* layer);
		KAJU_API void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	// To be defined in Client
	Application* CreateApplication();
}