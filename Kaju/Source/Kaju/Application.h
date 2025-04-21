#pragma once

#include "Core.h"

namespace KJ
{
	class KAJU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();
}