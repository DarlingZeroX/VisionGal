#pragma once
#include <VGEngine/Include/Core/Window.h>
#include <VGEngine/Include/Game/GameEngine.h>
#include <VGEngine/Include/Engine/ImGuiLayer.h>
#include <VGEngine/Include/Interface/EngineInterface.h>

namespace VisionGal::Editor
{
	class VGDesktopApplication : public IEngineApplication
	{
	public:
		VGDesktopApplication() = default;
		VGDesktopApplication(const VGDesktopApplication&) = delete;
		VGDesktopApplication& operator=(const VGDesktopApplication&) = delete;
		VGDesktopApplication(VGDesktopApplication&&) noexcept = default;
		VGDesktopApplication& operator=(VGDesktopApplication&&) noexcept = default;
		~VGDesktopApplication() override;

		void Initialize();
		void AddApplicationLayer(IEngineApplicationLayer* layer) override;
		void OnApplicationUpdate(float deltaTime) override;
		int ProcessEvent(const SDL_Event& event) override;
		void MakeCurrentRenderContext() override;

		void InitializeEditorPanels();

		void RunScene();
	private:
		void InitializeEditorUI();
		void AddImguiLayer();
	private:
		void OnRender();
		void OnUpdate(float delta);
		void OnFixedUpdate();
		void OnGUI();
	private:
		Ref<VGWindow> m_ApplicationWindow;
		Scope<ImguiOpengl3Layer> m_ImguiOpengl3Layer;
		Ref<CoreGameEngine> m_GameEngine;
	};


}
