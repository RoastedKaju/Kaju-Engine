project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir("ThirdParty/GLFW/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir("ThirdParty/GLFW/Intermediate/" .. outputdir .. "/%{prj.name}")

	glfwdir = "ThirdParty/GLFW"

	files
	{
		"%{glfwdir}/include/GLFW/glfw3.h",
		"%{glfwdir}/include/GLFW/glfw3native.h",
		"%{glfwdir}/src/glfw_config.h",
		"%{glfwdir}/src/context.c",
		"%{glfwdir}/src/init.c",
		"%{glfwdir}/src/input.c",
		"%{glfwdir}/src/monitor.c",

		"%{glfwdir}/src/null_init.c",
		"%{glfwdir}/src/null_joystick.c",
		"%{glfwdir}/src/null_monitor.c",
		"%{glfwdir}/src/null_window.c",

		"%{glfwdir}/src/platform.c",
		"%{glfwdir}/src/vulkan.c",
		"%{glfwdir}/src/window.c",
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
			"%{glfwdir}/src/x11_init.c",
			"%{glfwdir}/src/x11_monitor.c",
			"%{glfwdir}/src/x11_window.c",
			"%{glfwdir}/src/xkb_unicode.c",
			"%{glfwdir}/src/posix_module.c",
			"%{glfwdir}/src/posix_time.c",
			"%{glfwdir}/src/posix_thread.c",
			"%{glfwdir}/src/posix_module.c",
			"%{glfwdir}/src/glx_context.c",
			"%{glfwdir}/src/egl_context.c",
			"%{glfwdir}/src/osmesa_context.c",
			"%{glfwdir}/src/linux_joystick.c"
		}

	filter "system:macosx"
		pic "On"

		files
		{
			"%{glfwdir}/src/cocoa_init.m",
			"%{glfwdir}/src/cocoa_monitor.m",
			"%{glfwdir}/src/cocoa_window.m",
			"%{glfwdir}/src/cocoa_joystick.m",
			"%{glfwdir}/src/cocoa_time.c",
			"%{glfwdir}/src/nsgl_context.m",
			"%{glfwdir}/src/posix_thread.c",
			"%{glfwdir}/src/posix_module.c",
			"%{glfwdir}/src/osmesa_context.c",
			"%{glfwdir}/src/egl_context.c"
		}

		defines
		{
			"_GLFW_COCOA"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"%{glfwdir}/src/win32_init.c",
			"%{glfwdir}/src/win32_joystick.c",
			"%{glfwdir}/src/win32_module.c",
			"%{glfwdir}/src/win32_monitor.c",
			"%{glfwdir}/src/win32_time.c",
			"%{glfwdir}/src/win32_thread.c",
			"%{glfwdir}/src/win32_window.c",
			"%{glfwdir}/src/wgl_context.c",
			"%{glfwdir}/src/egl_context.c",
			"%{glfwdir}/src/osmesa_context.c"
		}

		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		symbols "on"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"