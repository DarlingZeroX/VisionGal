#pragma once
#include "../EngineConfig.h"
#include "../Core/Window.h"

namespace VisionGal
{
	struct VG_ENGINE_API ImguiOpengl3Layer
	{
		ImguiOpengl3Layer(Horizon::SDL3::Window* window, SDL_GLContext context);
		ImguiOpengl3Layer(const ImguiOpengl3Layer&) = delete;
		ImguiOpengl3Layer& operator=(const ImguiOpengl3Layer&) = delete;
		virtual ~ImguiOpengl3Layer();

		void BeginFrame();
		void EndFrame();
	private:
		void ImGuiBeginFrame();
		void ImGuiShutdown();
		void ImGuiRender();
	};

}