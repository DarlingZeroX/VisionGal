#pragma once
//#include "../include/CrossPlatformDefinitions.h"
#include "../imconfig.h"
#include <HCore/Include/HConfig.h>

#ifdef SDL3_WINDOW_SUPPORTED
#include <HCore/Include/Platform/SDL3/SDL3Window.h>
#endif

#include <HCore/Include/System/HWindow.h>

namespace ImGuiEx
{
	IMGUI_API void AddSDL3ImGuiWindowLayer(Horizon::HWindow& window, SDL_Renderer* renderer);

#ifdef SDL3_WINDOW_SUPPORTED
	class IMGUI_API SDL3RendererImGuiWindowLayer :public Horizon::SDL3::Layer
	{
	private:
		Horizon::SDL3::ISDL3Window* m_pWindow;
	public:
		SDL3RendererImGuiWindowLayer(Horizon::SDL3::ISDL3Window* window, SDL_Renderer* renderer);
		SDL3RendererImGuiWindowLayer(const SDL3RendererImGuiWindowLayer&) = delete;
		SDL3RendererImGuiWindowLayer& operator=(const SDL3RendererImGuiWindowLayer&) = delete;
		~SDL3RendererImGuiWindowLayer() override;

		int ProcessEvent(const SDL_Event& event) override;
	private:
		void ImGuiInit();
		void ImGuiShutdown();
	};
#endif

	class IMGUI_API Opengl3ImGuiWindowLayer :public Horizon::SDL3::Layer
	{
	private:
		Horizon::SDL3::ISDL3Window* m_pWindow;
	public:
		Opengl3ImGuiWindowLayer(Horizon::SDL3::ISDL3Window* window);
		Opengl3ImGuiWindowLayer(const Opengl3ImGuiWindowLayer&) = delete;
		Opengl3ImGuiWindowLayer& operator=(const Opengl3ImGuiWindowLayer&) = delete;
		~Opengl3ImGuiWindowLayer() override;

		int ProcessEvent(const SDL_Event& event) override;
	private:
		void ImGuiInit();
		void ImGuiShutdown();
	};
}