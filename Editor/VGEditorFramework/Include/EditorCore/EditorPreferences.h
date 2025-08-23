#pragma once
#include "../Config.h"
#include "EditorSettingInterface.h"

namespace VisionGal::Editor
{
	struct EditorPreferenceEditor : public EditorSettingInterface
	{
		EditorPreferenceEditor();
		~EditorPreferenceEditor() override = default;

		void OnGUI() override;
		void Load(const nlohmann::json& json) override;
		void Save(nlohmann::json& json) override;

		void EnsureDataNormal();

		std::string EditorName = "VisionGal Editor";
		int EditorWindowWidth = 1280;
		int EditorWindowHeight = 720;
		std::string EditorLanguage = "ZH-CN";
		std::string EditorTheme;
		int EditorFontSize = 17;
	};

	struct EditorPreferences
	{
		EditorPreferences();
		~EditorPreferences();

		EditorPreferenceEditor Editor;

		static void Load(EditorPreferences& preferences);
		static void Save(EditorPreferences& preferences);

		const std::vector<std::string>& GetPreferencesNameList() const { return m_PreferencesNameList; }
		std::string GetPreferencesNameByIndex(int index) const;
		EditorSettingInterface* GetPreferencesByName(const std::string& name);
		EditorSettingInterface* GetPreferencesByIndex(int index);

		static void ReadSettingFromFile(const std::filesystem::path& path, EditorSettingInterface& setting);
		static void SaveSettingToFile(const std::filesystem::path& path, EditorSettingInterface& setting);
	private:
		std::vector<std::string> m_PreferencesNameList;
	};
}