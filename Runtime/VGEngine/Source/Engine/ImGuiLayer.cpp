#include "Engine/ImGuiLayer.h"

#include <SDL3/SDL.h>
#include <HCore/Include/Platform/SDL3/SDL3Window.h>

#include <VGImgui/Include/Imgui/imgui_impl_sdl3.h>
#include <VGImgui/Include/Imgui/imgui_impl_opengl3.h>
#include <VGImgui/Include/Imgui/imgui.h>

namespace VisionGal
{
	ImguiOpengl3Layer::ImguiOpengl3Layer(Horizon::SDL3::Window* window, SDL_GLContext context)
	{
		//Init SDL3
		ImGui_ImplSDL3_InitForOpenGL(window->GetSDLWindow(), context);
		ImGui_ImplOpenGL3_Init(window->GetGLSLVersion());
	}

	ImguiOpengl3Layer::~ImguiOpengl3Layer()
	{
	}

	void ImguiOpengl3Layer::BeginFrame()
	{
		ImGuiBeginFrame();
	}

	void ImguiOpengl3Layer::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}
	}

	void ImguiOpengl3Layer::ImGuiBeginFrame()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiOpengl3Layer::ImGuiShutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiOpengl3Layer::ImGuiRender()
	{
	}

}