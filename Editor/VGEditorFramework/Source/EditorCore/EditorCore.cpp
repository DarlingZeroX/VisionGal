#include "EditorCore/EditorCore.h"
#include "VGEngine/Include/Project/ProjectSettings.h"

namespace VisionGal::Editor
{
	struct EditorCoreImp
	{
		EditorCoreImp() = default;
		~EditorCoreImp()
		{
			EditorPreferences::Save(Preferences);
			ProjectSettings::SaveProjectSettings();
		}

		static EditorCoreImp& GetInstance()
		{
			static EditorCoreImp imp;
			return imp;
		}

		EditorPreferences Preferences;
	};

    std::string EditorCore::GetEditorResourcePathVFS()
    {
        return "/editor/";
    }

    void EditorCore::LoadEditorPreferences()
    {
		EditorPreferences::Load(EditorCoreImp::GetInstance().Preferences);
    }

    EditorPreferences& EditorCore::GetEditorPreferences()
    {
		return EditorCoreImp::GetInstance().Preferences;
    }
}
