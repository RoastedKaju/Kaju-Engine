#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Kaju/Window.h"

namespace KJ
{
	class Application
	{
	public:
		KAJU_API Application();
		KAJU_API virtual ~Application();

		KAJU_API void Run();

		void OnEvent(Event& event);

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	// To be defined in Client
	Application* CreateApplication();
}