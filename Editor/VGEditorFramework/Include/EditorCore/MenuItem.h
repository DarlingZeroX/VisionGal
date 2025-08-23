#pragma once
#include <functional>
#include <string>
#include "../UIInterface.h"

namespace VisionGal::Editor
{
    struct MenuItem {
        std::string label;
        std::string shortcut;
        bool* p_selected;
        bool enabled;
        std::function<void()> callback;
    };

    class EditorUIMenu
    {
    public:

        void OnGUI();
        void AddMenuItem(const MenuItem& item);
    private:
        std::vector<MenuItem> m_MenuItem;
    };
}