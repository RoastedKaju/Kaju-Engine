#include "PCH.h"
#include "Application.h"

#include "Kaju/Events/ApplicationEvent.h"
#include "Kaju/Log.h"

KJ::Application::Application()
{

}

KJ::Application::~Application()
{

}

void KJ::Application::Run()
{
	WindowResizeEvent e(1280, 720);
	KJ_TRACE(e.ToString());

	while (true);
}