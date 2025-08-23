#pragma once
#include <VGImgui/IncludeImGuiEx.h>
#include <HCore/Include/System/HFileSystem.h>

namespace VisionGal::Editor {
	class NewDirectoryUITask : public ImGuiEx::ImTaskInterface
	{
	public:
		NewDirectoryUITask(const Horizon::fsPath& parentpath)
			:m_ParentPath(parentpath)
		{
		};

		void RenderUI(TaskContext& context) override;

	private:
		Horizon::fsPath m_ParentPath;

		std::string m_FileName;

		bool m_Error = false;
	};

}
