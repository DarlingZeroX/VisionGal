#pragma once
#include "../UIInterface.h"
#include <string>
#include <HCore/Include/File/NlohmannJson.h>
#include "VGImgui/Include/Imgui/imgui.h"

namespace VisionGal::Editor
{
	struct EditorSettingInterface: public IPanel
	{
		~EditorSettingInterface() override = default;

		virtual void Load(const nlohmann::json& json) = 0;
		virtual void Save(nlohmann::json& json) = 0;

		static ImGuiTableFlags GetSettingTableFlag();
		static void DrawTableColumnTitle(const std::string& title);
	};


}
