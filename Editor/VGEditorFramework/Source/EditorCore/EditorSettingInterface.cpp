#include "EditorCore/EditorSettingInterface.h"
#include "EditorCore/Localization.h"

namespace VisionGal::Editor
{
	ImGuiTableFlags EditorSettingInterface::GetSettingTableFlag()
	{
		return ImGuiTableFlags_Hideable |
			ImGuiTableFlags_BordersOuter |
			ImGuiTableFlags_BordersV |
			ImGuiTableFlags_BordersInner |
			ImGuiTableFlags_Resizable;
	}

	void EditorSettingInterface::DrawTableColumnTitle(const std::string& title)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(EditorText{ title }.c_str());
		ImGui::TableNextColumn();
	}
}
