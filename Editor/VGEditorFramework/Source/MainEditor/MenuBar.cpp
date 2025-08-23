#include "MainEditor/MenuBar.h"
//#include "VGImgui/Include/ImGuiEx/IconFont/IconsFontAwesome5Pro.h"
#include <VGImgui/IncludeImGuiEx.h>
#include "PanelManager.h"
#include "EditorCore/Localization.h"
#include "EditorCore/EdtiorScene.h"
#include "MainEditor/MainPanel.h"
#include "VGEngine/Include/Engine/Manager.h"
#include "VGEngine/Include/Engine/VGEngine.h"

namespace VisionGal::Editor
{
	void EditorMenuBar::OnGUI()
	{
		static bool s_ShowImguiStyleEditor = false;
		auto& style = ImGui::GetStyle();
		auto borderSize = style.WindowBorderSize;
		style.WindowBorderSize = 0.0f;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 7));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 4));

		if (ImGui::BeginMainMenuBar())
		{
			//HandleDraggingWindow();

			// 文件菜单
			if (ImGui::BeginMenu(EditorText{ "File" }.c_str()))
			{
				ImGui::Separator();
				if (ImGui::MenuItemEx(EditorText{ "New Scene" }.c_str(), " ", "CTRL+N"))
				{
					EditorScene::NewScene();
				}
				if (ImGui::MenuItemEx(EditorText{ "Open Scene" }.c_str(), ICON_FA_FILE, "CTRL+O"))
				{
					EditorScene::OpenSceneByFileDialog();
				}

				ImGui::Separator();
				if (ImGui::MenuItemEx(EditorText{ "Save Scene" }.c_str(), ICON_FA_SAVE, "CTRL+S"))
				{
					EditorScene::SaveCurrentScene();
				}

				if (ImGui::MenuItemEx(EditorText{ "Save Scene As..." }.c_str(), ICON_FA_SAVE))
				{
					EditorScene::SaveCurrentSceneAs();
				}

				ImGui::Separator();

				//if (ImGui::MenuItem(EditorText{ "New Project" }.c_str(), ""))
				//{
				//}
				//if (ImGui::MenuItem(EditorText{ "Open Project" }.c_str(), ""))
				//{
				//}
				//if (ImGui::MenuItemEx(EditorText{ "Save Project" }.c_str(), ICON_FA_SAVE, ""))
				//{
				//}

				if (ImGui::MenuItem(EditorText{ "Build Setting..." }.c_str()))
				{
					PanelManager::GetInstance()->OpenPanel("BuildSettings");
				}

				ImGui::Separator();

				if (ImGui::MenuItemEx(EditorText{ "Exit" }.c_str(), ICON_FA_TIMES))
				{
					VGEngine::Get()->RequestExit();
				}
				ImGui::EndMenu();
			}

			// 编辑
			if (ImGui::BeginMenu(EditorText{ "Edit" }.c_str()))
			{
				//if (ImGui::MenuItemEx("Undo", " ", "CTRL+Z")) {}
				//if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				//ImGui::Separator();
				//if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				//if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				//if (ImGui::MenuItem("Paste", "CTRL+V")) {}

				if (ImGui::MenuItem(EditorText{ "Imgui Demo" }.c_str()))
				{
					s_ShowImguiStyleEditor = true;
				}

				if (ImGui::MenuItem(EditorText{ "Project Setting..." }.c_str()))
				{
					PanelManager::GetInstance()->OpenPanel("ProjectSetting");
				}

				if (ImGui::MenuItem(EditorText{ "Preferences..." }.c_str()))
				{
					PanelManager::GetInstance()->OpenPanel("EditorPreferences");
				}
				ImGui::EndMenu();
			}

			// 窗口菜单
			if (ImGui::BeginMenu(EditorText{ "Window" }.c_str()))
			{
				auto* panelManager = PanelManager::GetInstance();
				auto* mainWindow = dynamic_cast<EditorMainWindow*>(panelManager->GetPanelWithID("EditorMainWindow"));
				if (mainWindow)
				{
					mainWindow->TraversePanels([this](IEditorPanel* panel)
						{
							if (panel == nullptr)
								return;
							std::string icon;
							if (panel->IsWindowOpened())
								icon = ICON_FA_CHECK;
							else
								icon = ICON_FA_TIMES;

							if (ImGui::MenuItemEx(EditorText{ panel->GetWindowName() }.c_str(), icon.c_str()))
							{
								panel->OpenWindow(!panel->IsWindowOpened());
							}
						});
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(EditorText{ "Help" }.c_str()))
			{
				ImGui::EndMenu();
			}

			//HandleWindowControl();
			ImGui::EndMainMenuBar();
		}

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();

		style.WindowBorderSize = borderSize;

		if (s_ShowImguiStyleEditor)
		{
			ImGui::ShowDemoWindow(&s_ShowImguiStyleEditor);
		}
	}

	std::string EditorMenuBar::GetWindowFullName()
	{
		return "EditorMenuBar";
	}

	std::string EditorMenuBar::GetWindowName()
	{
		return "EditorMenuBar";
	}

	void EditorMenuBar::OpenWindow(bool open)
	{
	}

	bool EditorMenuBar::IsWindowOpened()
	{
		return true;
	}
}
