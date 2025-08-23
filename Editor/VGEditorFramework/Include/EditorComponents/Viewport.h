#pragma once
#include "../Config.h"
#include "../UIInterface.h"
#include <vector>
#include <HCore/Include/HConfig.h>
#include <VGImgui/IncludeImGui.h>
#include <VGEngine/Include/Core/Viewport.h>

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API EditorViewport : public IEditorPanel
	{
	public:
		EditorViewport(Viewport* viewport);
		EditorViewport(const EditorViewport&) = delete;
		EditorViewport& operator=(const EditorViewport&) = delete;
		EditorViewport(EditorViewport&&) noexcept = default;
		EditorViewport& operator=(EditorViewport&&) noexcept = default;
		~EditorViewport() override = default;

		void OnGUI() override;

		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;
	private:
		Viewport* m_Viewport;
		std::vector<Ref<ISidebarComponent>> m_Components;
		bool m_IsOpen = true;
	};



}
