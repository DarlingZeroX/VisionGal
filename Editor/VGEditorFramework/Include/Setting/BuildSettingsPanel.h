#pragma once
#include "../Config.h"
#include "../EditorCore/EditorSettingInterface.h"
#include "VGEngine/Include/Project/ProjectBuilder.h"

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API BuildSettingsPanel : public IEditorPanel
	{
	public:
		BuildSettingsPanel();
		BuildSettingsPanel(const BuildSettingsPanel&) = default;
		BuildSettingsPanel& operator=(const BuildSettingsPanel&) = default;
		BuildSettingsPanel(BuildSettingsPanel&&) noexcept = default;
		BuildSettingsPanel& operator=(BuildSettingsPanel&&) noexcept = default;
		~BuildSettingsPanel() override = default;

		void OnGUI() override;
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;

	private:
		void OnGUIInternal();
		void OpenBuildOutputDirectoryDialog();
		bool ApplicationMainSceneUI();
		bool BuildOutputDirectoryUI();

		void RenderBuildProcess();
	private:
		bool m_IsOpen = false;
		int m_SelectedPanelIndex = 0;
		EditorSettingInterface* m_SelectedPanel = nullptr;

		std::string m_ProjectBuildOutputDirectory;
		std::string m_ApplicationMainScene;

		std::vector<std::string> m_TargetPlatforms;
		std::string m_TargetPlatform;

		ProjectBuilder::BuildContext m_BuildContext;
	};

}
