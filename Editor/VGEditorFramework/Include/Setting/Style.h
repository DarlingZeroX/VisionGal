#pragma once
#include "../Config.h"

namespace VisionGal::Editor
{
	struct VG_EDITOR_FRAMEWORK_API EditorStyle
	{
		static void DarkTheme();

		static const std::vector<std::string>& GetEditorThemes();

		static bool SetTheme(const std::string& name);
	};
}
