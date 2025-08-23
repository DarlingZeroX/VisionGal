#pragma once
#include "../UIInterface.h"
#include <string>
#include <functional>
#include <VGEngine/Include/Core/Core.h>

namespace VisionGal::Editor
{
    struct EditorScene
    {
        static void OpenSaveCurrentSceneDialog(const std::function<void(int)>& callback);

        static void NewScene();

        static bool OpenNewScene(const VGPath& path);

        static void OpenSceneByFileDialog();

        static bool SaveCurrentScene();

        static bool SaveCurrentSceneAs();
    };
}
