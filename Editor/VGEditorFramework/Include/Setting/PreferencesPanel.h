#pragma once
#include "../Config.h"
#include "../EditorCore/EditorSettingInterface.h"

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API PreferencesPanel : public IEditorPanel
	{
	public:
		PreferencesPanel() = default;
		PreferencesPanel(const PreferencesPanel&) = default;
		PreferencesPanel& operator=(const PreferencesPanel&) = default;
		PreferencesPanel(PreferencesPanel&&) noexcept = default;
		PreferencesPanel& operator=(PreferencesPanel&&) noexcept = default;
		~PreferencesPanel() override = default;

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
