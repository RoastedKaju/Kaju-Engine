#include "PCH.h"
#include "Kaju/Log.h"
#include "Kaju/Events/ApplicationEvent.h"
#include "Kaju/Events/KeyEvent.h"
#include "Kaju/Events/MouseEvent.h"
#include "WindowsWindow.h"

namespace KJ
{
	static bool s_glfwInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		KJ_CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
	}

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

			// Error callback
			glfwSetErrorCallback(&GLFWErrorCallback);

			s_glfwInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVsync(true);

		// GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				WindowCloseEvent event;
				data.eventCallback(event);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) 
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			});



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