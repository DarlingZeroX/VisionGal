#pragma once
#include <VGEngine/Include/Core/Window.h>
#include <VGEngine/Include/Game/GameEngine.h>
#include <VGEngine/Include/Engine/ImGuiLayer.h>
#include <VGEngine/Include/Interface/EngineInterface.h>

namespace VisionGal::Editor
{
	class VGEditorApplication: public IEngineApplication
	{
	public:
		VGEditorApplication() = default;
		VGEditorApplication(const VGEditorApplication&) = delete;
		VGEditorApplication& operator=(const VGEditorApplication&) = delete;
		VGEditorApplication(VGEditorApplication&&) noexcept = default;
		VGEditorApplication& operator=(VGEditorApplication&&) noexcept = default;
		~VGEditorApplication() override;

		void Initialize();
		void AddApplicationLayer(IEngineApplicationLayer* layer) override;
		void OnApplicationUpdate(float deltaTime) override;
		int ProcessEvent(const SDL_Event& event) override;
		void MakeCurrentRenderContext() override;

		void InitializeEditorPanels();
	private:
		void InitializeEditorUI();
		void AddImguiLayer();
	private:
		void OnRender();
		void OnUpdate(float delta);
		void OnFixedUpdate();
		void OnGUI();
	private:
		Ref<VGWindow> m_EditorWindow;
		Scope<ImguiOpengl3Layer> m_ImguiOpengl3Layer;
		Ref<CoreGameEngine> m_GameEngine;
	};


}
