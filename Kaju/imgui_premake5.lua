project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir("ThirdParty/ImGui/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir("ThirdParty/ImGui/Intermediate/" .. outputdir .. "/%{prj.name}")

	imguidir = "ThirdParty/ImGui"

	files
	{
		"%{imguidir}/imconfig.h",
		"%{imguidir}/imgui.h",
		"%{imguidir}/imgui.cpp",
		"%{imguidir}/imgui_draw.cpp",
		"%{imguidir}/imgui_internal.h",
		"%{imguidir}/imgui_widgets.cpp",
		"%{imguidir}/imstb_rectpack.h",
		"%{imguidir}/imstb_textedit.h",
		"%{imguidir}/imstb_truetype.h",
		"%{imguidir}/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"