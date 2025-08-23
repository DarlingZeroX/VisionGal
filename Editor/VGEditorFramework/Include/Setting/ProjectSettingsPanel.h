#pragma once
#include "../Config.h"
#include "../EditorCore/EditorSettingInterface.h"

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API ProjectSettingPanel : public IEditorPanel
	{
	public:
		ProjectSettingPanel() = default;
		ProjectSettingPanel(const ProjectSettingPanel&) = default;
		ProjectSettingPanel& operator=(const ProjectSettingPanel&) = default;
		ProjectSettingPanel(ProjectSettingPanel&&) noexcept = default;
		ProjectSettingPanel& operator=(ProjectSettingPanel&&) noexcept = default;
		~ProjectSettingPanel() override = default;

		void OnGUI() override;
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;

	private:
		bool m_IsOpen = false;
		int m_SelectedPanelIndex = 0;
		EditorSettingInterface* m_SelectedPanel = nullptr;
	};

}
