#pragma once
#include "../Config.h"
#include "../UIInterface.h"
#include <vector>
#include <HCore/Include/HConfig.h>
#include <VGImgui/IncludeImGui.h>

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API EditorSideBar : public IEditorPanel
	{
	public:
		EditorSideBar() = default;
		EditorSideBar(const EditorSideBar&) = default;
		EditorSideBar& operator=(const EditorSideBar&) = default;
		EditorSideBar(EditorSideBar&&) noexcept = default;
		EditorSideBar& operator=(EditorSideBar&&) noexcept = default;
		~EditorSideBar() override = default;

		void OnGUI() override;
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;
		void AddComponent(const Ref<ISidebarComponent>& component);
	private:
		void DrawDownStatusBar();
	private:
		//std::vector<Ref<IPanel>> m_Panels;
		std::vector<Ref<ISidebarComponent>> m_Components;
	};

}
