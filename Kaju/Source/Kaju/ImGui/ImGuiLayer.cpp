#include "PCH.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Kaju/Application.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

KJ::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
}

KJ::ImGuiLayer::~ImGuiLayer()
{
}

void KJ::ImGuiLayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	ImGui_ImplOpenGL3_Init("#version 410");

}

void KJ::ImGuiLayer::OnDetach()
{
}

void KJ::ImGuiLayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	Application& application = *Application::Get();
	io.DisplaySize = ImVec2((float)application.GetWindow().GetWidth(), (float)application.GetWindow().GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void KJ::ImGuiLayer::OnEvent(Event& event)
{
}
