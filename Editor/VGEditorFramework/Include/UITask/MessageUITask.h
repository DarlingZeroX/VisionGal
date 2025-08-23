#pragma once
#include <VGImgui/IncludeImGuiEx.h>
#include <VGEngine/Include/Core/Core.h>
#include <HCore/Include/System/HFileSystem.h>

namespace VisionGal::Editor
{
	class MessageUITask : public ImGuiEx::ImTaskInterface
	{
	public:
		MessageUITask() = default;
		MessageUITask(const MessageUITask&) = default;
		MessageUITask& operator=(const MessageUITask&) = default;
		MessageUITask(MessageUITask&&) noexcept = default;
		MessageUITask& operator=(MessageUITask&&) noexcept = default;
		MessageUITask(String const& title, String const& text);

		void SetChoices(const std::vector<String>& choices);
		void SetCallback(const std::function<void(int)>& callback);
		void RenderUI(TaskContext& context) override;
	private:
		String m_Title;
		String m_Text;
		std::vector<String> m_Choices;
		std::function<void(int)> m_Callback;
	};

}
