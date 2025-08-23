#pragma once
#include "../Config.h"
#include "../EditorCore/EditorSettingInterface.h"

namespace VisionGal::Editor
{
	struct ProjectSettingsEditorWrapper : public EditorSettingInterface
	{
		ProjectSettingsEditorWrapper() = default;
		~ProjectSettingsEditorWrapper() override = default;

		void OnGUI() override;

		void Load(const nlohmann::json& json) override {};
		void Save(nlohmann::json& json) override {};
	};

	struct ProjectSettingsApplicationWrapper : public EditorSettingInterface
	{
		ProjectSettingsApplicationWrapper() = default;
		~ProjectSettingsApplicationWrapper() override = default;

		void OnGUI() override;

		void Load(const nlohmann::json& json) override {};
		void Save(nlohmann::json& json) override {};
	};

	struct ProjectSettingsGalGameWrapper : public EditorSettingInterface
	{
		ProjectSettingsGalGameWrapper() = default;
		~ProjectSettingsGalGameWrapper() override = default;

		void OnGUI() override;

		void Load(const nlohmann::json& json) override {};
		void Save(nlohmann::json& json) override {};
	};

	struct ProjectSettingsWrapper
	{
		ProjectSettingsWrapper();
		~ProjectSettingsWrapper();

		static const std::vector<std::string>& GetProjectSettingsNameList();
		static std::string GetProjectSettingsNameByIndex(int index);
		static EditorSettingInterface* GetProjectSettingsByName(const std::string& name);
		static EditorSettingInterface* GetProjectSettingsByIndex(int index);

		//static void ReadSettingFromFile(const std::filesystem::path& path, EditorSettingInterface& setting);
		//static void SaveSettingToFile(const std::filesystem::path& path, EditorSettingInterface& setting);
	};
}