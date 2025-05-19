#include "PCH.h"
#include "Kaju/Log.h"
#include "WindowsWindow.h"

namespace KJ
{
	static bool s_glfwInitialized = false;

	// From the base class Windows
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		KJ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		// Initialize glfw only once per launch because we can have multiple windows
		if (!s_glfwInitialized)
		{
			int success = glfwInit();
			// Assert check
			KJ_CORE_ASSERT(success, "Could not initialize GLFW.");

			s_glfwInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVsync(true);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVsync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_data.vsync = enabled;
	}

	bool WindowsWindow::IsVsync() const
	{
		return m_data.vsync;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}
}