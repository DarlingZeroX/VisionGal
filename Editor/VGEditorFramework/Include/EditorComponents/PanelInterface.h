#pragma once
#include <HCore/Include/HConfig.h>
#include <VGImgui/IncludeImGui.h>
#include <VGImgui/IncludeImGuiEx.h>

namespace Horizon::Editor {
	struct PanelInterface : ImGuiEx::ImPanelInterface
	{
		~PanelInterface() override = default;
	};
}
