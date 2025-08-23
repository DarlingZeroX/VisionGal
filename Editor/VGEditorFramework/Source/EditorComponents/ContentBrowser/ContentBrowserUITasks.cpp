#include "EditorComponents/ContentBrowser/ContentBrowserUITasks.h"
#include "EditorCore/ContentBrowser.h"
#include "EditorCore/Localization.h"
#include <VGImgui/IncludeImGuiEx.h>

namespace VisionGal::Editor {
	void NewDirectoryUITask::RenderUI(TaskContext& context)
	{
		if (context.ForceStop)
			return;

		ImGui::OpenPopup("New Directory");

		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("New Directory", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::Text(EditorText{ "New Directory" }.c_str());
			ImGuiEx::InputTextWithHint("##DirectoryName", EditorText{ "Name" }.c_str(), m_FileName);

			if (ImGui::Button(EditorText{ "Ok" }.c_str()))
			{
				const auto fullPath = m_ParentPath / m_FileName;

				if (!Horizon::HFileSystem::ExistsDirectory(fullPath))
				{
					if (Horizon::HFileSystem::CreateDirectory(fullPath))
					{
						context.IsFinished = true;
						ContentBrowser::GetInstancePtr()->RefreshDirectory();
						ContentBrowser::GetInstancePtr()->RefreshDirectoryTreeRoot();
					}
					else
					{
						m_Error = true;
					}
				}
				else
				{
					m_Error = true;
				}
			}

			ImGui::SameLine();

			if (ImGui::Button(EditorText{ "Cancel" }.c_str()))
			{
				context.IsFinished = true;
			}

			if (m_Error)
			{
				ImGui::Text("Directory Exist!!");
			}

			ImGui::EndPopup();
		}

	}
}
