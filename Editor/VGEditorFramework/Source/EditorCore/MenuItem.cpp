#include "EditorCore/MenuItem.h"
#include <VGImgui/IncludeImGui.h>

namespace VisionGal::Editor
{
	void EditorUIMenu::OnGUI()
	{
		for (auto& item : m_MenuItem) {
			if (ImGui::MenuItem(item.label.c_str(), item.shortcut.c_str(), item.p_selected, item.enabled)) {
				if (item.callback)
				{
					item.callback();
				}
			}
		}
	}

	void EditorUIMenu::AddMenuItem(const MenuItem& item)
	{
		m_MenuItem.push_back(item);
	}
}


