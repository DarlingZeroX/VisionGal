#include "MainEditor/SideBar.h"
//#include "VGImgui/Include/ImGuiEx/IconFont/IconsFontAwesome5Pro.h"
#include <VGImgui/IncludeImGuiEx.h>

namespace VisionGal::Editor
{
	void EditorSideBar::OnGUI()
	{
		DrawDownStatusBar();
	}

	std::string EditorSideBar::GetWindowFullName()
	{
		return "EditorSideBar";
	}

	std::string EditorSideBar::GetWindowName()
	{
		return "EditorSideBar";
	}

	void EditorSideBar::OpenWindow(bool open)
	{
	}

	bool EditorSideBar::IsWindowOpened()
	{
		return true; // Always opened
	}

	void EditorSideBar::AddComponent(const Ref<ISidebarComponent>& component)
	{
		m_Components.push_back(component);
	}

	void EditorSideBar::DrawDownStatusBar()
	{
		constexpr ImGuiWindowFlags barFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
		const float height = ImGui::GetFrameHeight() * 1.5f;

		ImGuiEx::ScopedStyle style;
		style.PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		style.PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7, 7));

		if (ImGui::BeginViewportSideBar(
			"##DownMenuBar",
			ImGui::GetMainViewport(),
			ImGuiDir_Down,
			height,
			barFlags
		))
		{
			// 阴影
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			static ImGuiEx::RectFilledMultiColor bg;
			ImVec2 region = ImGui::GetContentRegionMax();
			//bg.SetRegionAutoOffest(region, 0.0f, 0.0f, -50.0f, -region.y - 2.0f);
			bg.SetRegionAutoOffest(region, 0.0f, region.x);
			bg.SetColLeft(Horizon::float4(.0f, .0f, .0f, 0.231f));
			bg.WindowDraw();

			// Sidebar的按钮组件UI
			for (auto& com:m_Components)
			{
				com->OnSideBarUI();
			}
		}

		ImGui::End();

		// 实际组件的UI
		for (auto& com : m_Components)
		{
			com->OnGUI();
		}
	}

}
