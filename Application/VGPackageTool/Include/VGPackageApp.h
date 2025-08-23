#pragma once
#include <VGEngine/Include/Core/Window.h>
#include <VGEngine/Include/Game/GameEngine.h>
#include <VGEngine/Include/Engine/ImGuiLayer.h>
#include <VGEngine/Include/Interface/EngineInterface.h>

namespace VisionGal::Editor
{
	class VGPackageApp : public IEngineApplication
	{
	public:
		VGPackageApp() = default;
		VGPackageApp(const VGPackageApp&) = delete;
		VGPackageApp& operator=(const VGPackageApp&) = delete;
		VGPackageApp(VGPackageApp&&) noexcept = default;
		VGPackageApp& operator=(VGPackageApp&&) noexcept = default;
		~VGPackageApp() override;

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
		Ref<VGWindow> m_ApplicationWindow;
		Scope<ImguiOpengl3Layer> m_ImguiOpengl3Layer;
	};


}
