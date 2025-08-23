#pragma once
#include <VGImgui/IncludeImGuiEx.h>
#include <VGEngine/Include/Core/Core.h>
#include <HCore/Include/System/HFileSystem.h>

namespace VisionGal::Editor
{
	class NewProjectUITask : public ImGuiEx::ImTaskInterface
	{
	public:
		NewProjectUITask();
		NewProjectUITask(const NewProjectUITask&) = default;
		NewProjectUITask& operator=(const NewProjectUITask&) = default;
		NewProjectUITask(NewProjectUITask&&) noexcept = default;
		NewProjectUITask& operator=(NewProjectUITask&&) noexcept = default;
		~NewProjectUITask() override = default;

		void RenderUI(TaskContext& context) override;
	private:
		// 打开项目位置选择对话框
		void OpenProjectLocationDialog();

		// 创建项目并弹出通知
		void CreateProject();

		String m_Title;
		String m_Text;

		std::string m_ProjectName;
		std::string m_ProjectLocation;
	};

}
