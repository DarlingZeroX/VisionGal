#pragma once
#include "../Config.h"
#include "EditorPreferences.h"
#include <functional>
#include <string>

namespace VisionGal::Editor
{
    struct VG_EDITOR_FRAMEWORK_API EditorCore
    {
    	static std::string GetEditorResourcePathVFS();

		static void LoadEditorPreferences();
		static EditorPreferences& GetEditorPreferences();
    };
}