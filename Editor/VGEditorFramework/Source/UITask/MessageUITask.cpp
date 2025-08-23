#include "UITask/MessageUITask.h"
#include "EditorCore/Localization.h"

namespace VisionGal::Editor {

	MessageUITask::MessageUITask(String const& title, String const& text)
		:m_Title(title),m_Text(text)
	{

	}

	void MessageUITask::SetChoices(const std::vector<String>& choices)
	{
		m_Choices = choices;
	}

	void MessageUITask::SetCallback(const std::function<void(int)>& callback)
	{
		m_Callback = callback;
	}

	void MessageUITask::RenderUI(TaskContext& context)
	{
		if (context.ForceStop)
			return;

		ImGui::OpenPopup("New Message");

		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		bool hasChoice = false;
		int choiceIndex = 0;

		if (ImGui::BeginPopupModal("New Message", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::Text(EditorText{ m_Title }.c_str());
			ImGui::Text(EditorText{ m_Text }.c_str());

			{	ImGuiEx::ScopedID uiid("New UI Message");

				for (int i = 0; i < m_Choices.size(); ++i)
				{
					choiceIndex = i;
					if (ImGui::Button(EditorText{ m_Choices[i] }.c_str()))
					{
						hasChoice = true;
						break;
					}

					ImGui::SameLine();
				}
			}
			ImGui::EndPopup();
		}

		if (hasChoice)
		{
			context.IsFinished = true;

			if (m_Callback)
			{
				m_Callback(choiceIndex);
			}
		}
	}
}
