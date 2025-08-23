#pragma once
#include "../Config.h"
#include "../EditorComponents/PanelInterface.h"
#include <VGImgui/Include/ImGuiColorTextEdit/TextEditor.h>
#include "VGEngine/Include/Core/Core.h"

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API TextEditorPanel : public IEditorPanel
	{
	public:
		TextEditorPanel();
		~TextEditorPanel() override;

		void OnGUI() override;
		bool OpenTextFile(const VGPath& path);

		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;
	private:
		class ShaderEditorList;
		void RenderTextEditorUI();
		void RenderFileListUI();

		bool m_bItemDragging;
		bool m_IsTextChanged = false;

		std::set<std::string> m_FileList;
		std::unique_ptr<ShaderEditorList> m_ListPanel;
		//ImGuiTextEditorOriginal::TextEditor m_TexEditor;
		ImGuiTextEditor::TextEditor m_TexEditor;

		std::string m_Text;
		std::string m_CurrentTextPath;

		bool m_HasText = false;
		bool m_IsOpen = false;
	};
}
