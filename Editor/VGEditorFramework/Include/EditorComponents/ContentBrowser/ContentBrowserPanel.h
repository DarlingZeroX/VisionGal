#pragma once
#include "../../Config.h"
#include "../PanelInterface.h"
#include "../../EditorCore/ContentBrowser.h"
#include <VGEngine/Include/Resource/Texture2D.h>

namespace VisionGal::Editor {
	class VG_EDITOR_FRAMEWORK_API ContentBrowserPanel: public IEditorPanel
	{
		using pfsPath = Horizon::fsPath;
	public:
		ContentBrowserPanel();
		ContentBrowserPanel(const pfsPath& path);
		ContentBrowserPanel(const ContentBrowserPanel&) = delete;
		ContentBrowserPanel& operator=(const ContentBrowserPanel&) = delete;
		ContentBrowserPanel(ContentBrowserPanel&&) noexcept = default;
		ContentBrowserPanel& operator=(ContentBrowserPanel&&) noexcept = default;
		~ContentBrowserPanel() override;

		void Toggle();
		void OnGUI() override;
		 
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;
	private:
		void RefreshDirectory();

		// 左边的目录树 Left directory tree
		void DrawRootDirectoryTree();
		void DrawDirectoryTree(ContentBrowserDirectory& node);
		// 点击打开目录
		void DirectoryItemFunction(ContentBrowserDirectory& node);

		// 右边的内容浏览器 Right content browser
		void DrawContentBrowser();
		void DrawBrowserHeader();
		void DrawBrowserList();
		void DrawBrowserListItem();

		// 单个文件的功能 Item
		void DrawPath(const pfsPath& path);
		bool ItemFunction(ContentBrowserItem& item);
		void ItemBeginDragSource(const ContentBrowserItem& item);
		void ItemBeginDropTarget(const ContentBrowserItem& item);

		// 上下文菜单 Context menu
		bool ItemContextMenu(ContentBrowserItem& item);
		void ContentBrowserContextMenu(const pfsPath& path);
	private:
	//	bool ImageButton(DLG::ITextureView* view, float width, float height);
		void* GetFileIcon(ContentBrowserItem& item);
	public:
		struct ImContentBrowserWindow;
		ContentBrowser* m_pContentBrowser;

		bool m_ContentBrowserOpenFlag = true;
		bool m_IsAnyContentBrowserItemHovered = false;

		std::unordered_map<std::string, Ref<Texture2D>> m_Icons;
	};
}
