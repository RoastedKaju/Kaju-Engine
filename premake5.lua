workspace "Kaju"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Kaju Project --
project "Kaju"
	location "Kaju"
	kind "SharedLib"
	language "C++"

	targetdir("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Include/**.h",
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Include",
		"%{prj.name}/ThirdParty/SPD/include"
	}

	-- Enable PCH
	pchheader "PCH.h"
	pchsource "%{prj.name}/Source/PCH.cpp"

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions { "/utf-8" }

		defines
		{
			"KJ_PLATFORM_WINDOWS",
			"KJ_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "KJ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KJ_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "KJ_DIST"
		optimize "On"

-- Sandbox Project --
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Kaju/ThirdParty/SPD/include",
		"Kaju/Source"
	}

	links
	{
		"Kaju"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions { "/utf-8" }

		defines
		{
			"KJ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "KJ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KJ_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "KJ_DIST"
		optimize "On"