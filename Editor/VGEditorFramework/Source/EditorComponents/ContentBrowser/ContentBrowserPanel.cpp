#include "EditorComponents/ContentBrowser/Thumbnial.h"
#include "EditorComponents/ContentBrowser/ContentBrowserPanel.h"
#include "EditorComponents/ContentBrowser/ContentBrowserUITasks.h"

#include <VGImgui/IncludeImGuiEx.h>
#include <HCore//Include/Core/HStringTools.h>
#include <HCore/Include/Utils/HFileSystemGenerator.h>

#include "AssetEditor/AssetEditor.h"
#include "EditorCore/EditorCore.h"
#include "EditorCore/Localization.h"
#include "VGEngine/Include/Asset/AssetFactory.h"
#include "VGEngine/Include/Core/VFS.h"
#include "VGEngine/Include/Interface/Loader.h"

#ifdef GetCurrentDirectory
#undef GetCurrentDirectory
#endif

namespace VisionGal::Editor {
	ContentBrowserPanel::ContentBrowserPanel()
	{
		m_pContentBrowser = ContentBrowser::GetInstancePtr();
		//RefreshDirectory();

		m_Icons["Image"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/image.png");
		m_Icons["Folder"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/folder.png");
		m_Icons["File"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/file.png");
		m_Icons["LuaScript"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/lua.png");
		m_Icons["Scene"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/scene.png");
		m_Icons["HTML"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/html.png");
		m_Icons["CSS"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/css.png");
		m_Icons["Sound"] = LoadObject<Texture2D>(EditorCore::GetEditorResourcePathVFS() + "icons/sound.png");
	}

	ContentBrowserPanel::ContentBrowserPanel(const pfsPath& path)
	{
		ContentBrowser::Create(path);

		//ThumbnailManager::Create(gfx, project);

		m_pContentBrowser = ContentBrowser::GetInstancePtr();

		//EditorEventBus::Instance().AddListener(Events::EditorEventType::FileDropped,
		//	[this](const Events::HEditorEvent* eEvent, const Events::HEventDesc& eDesc)
		//	{
		//		auto* fileDropEvent = ((Events::FileDroppedEvent*)eEvent);
		//
		//		Importer::HAssetImporter::ImportAsset(
		//			fileDropEvent->Path,
		//			//	HVirtualFileSystem::PfsPathToHPath(m_CurrentDirectory)
		//			HVirtualFileSystem::PfsPathToHPath(HContentBrowser::GetInstancePtr()->GetCurrentDirectory())
		//
		//		);
		//	});
	}

	ContentBrowserPanel::~ContentBrowserPanel()
	{
	}

	void ContentBrowserPanel::Toggle()
	{
		m_ContentBrowserOpenFlag = !m_ContentBrowserOpenFlag;
	}

	void ContentBrowserPanel::OnGUI()
	{
		if (!m_ContentBrowserOpenFlag)
			return;

		ImGuiEx::ScopedStyleVar winBorder(ImGuiStyleVar_WindowBorderSize, 1.0f);
		ImGuiEx::ScopedStyleVar framePadding(ImGuiStyleVar_FramePadding, ImVec2(4, 5));
		ImGuiEx::ScopedStyleColor frameBackGround(ImGuiCol_MenuBarBg, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

		//SetContentBrowserPosition();

		//ImContentBrowserWindow{ this }.OnGUI();
		//ThumbnailManager::GetInstance().Tick();

		if (ImGui::Begin(GetWindowFullName().c_str(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar))
		{
			// 菜单栏 Menu bar
			if (ImGui::BeginMenuBar())
			{
				// Top shadow
				ImGuiEx::RectFilledMultiColor bg;
				const ImVec2 region = ImGui::GetContentRegionAvail();
				//bg.SetRegionAutoOffest(region, 0.0f, 0.0f, 0, region.y);
				bg.SetRegionAutoOffest(region, 0.0f, region.x, 0, 0);
				bg.SetColTop(Horizon::float4(.0f, .0f, .0f, 0.431f));
				bg.WindowDraw();

				DrawBrowserHeader();

				ImGui::EndMenuBar();
			}

			// 左侧目录树
			ImGui::BeginChild("Content Browser Left", ImVec2(200, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
			DrawRootDirectoryTree();
			ImGui::EndChild();

			ImGui::SameLine();

			// 右侧内容浏览器
			ImGui::BeginChild("Content Browser Right",ImVec2(0, 0), ImGuiChildFlags_Borders);
			DrawContentBrowser();
			ContentBrowserContextMenu(m_pContentBrowser->GetCurrentBrowserDirectory());
			ImGui::EndChild();
		}
		ImGui::End();
	}

	std::string ContentBrowserPanel::GetWindowFullName()
	{
		return EditorText{ GetWindowName(),ICON_FA_FOLDERS }.GetText();
	}

	std::string ContentBrowserPanel::GetWindowName()
	{
		return "Content Browser";
	}

	void ContentBrowserPanel::OpenWindow(bool open)
	{
		m_ContentBrowserOpenFlag = open;
	}

	bool ContentBrowserPanel::IsWindowOpened()
	{
		return m_ContentBrowserOpenFlag;
	}

	void ContentBrowserPanel::DrawRootDirectoryTree()
	{
		//目录右边的分割阴影 Right shadow
		ImGuiEx::RectFilledMultiColor shadow;
		ImVec2 region = ImGui::GetContentRegionAvail();
		shadow.SetRegionAutoOffest(region, region.x - 10.0f, 10.0f);
		shadow.SetColRight(Horizon::float4(.0f, .0f, .0f, 0.431f));
		shadow.WindowDraw();

		// 背景 Background
		ImGuiEx::RectFilled bg;
		bg.SetRegionAutoOffest(region);
		bg.SetCol(Horizon::float4(.0f, .0f, .0f, 0.800f));
		bg.WindowDraw();

		//总Assets目录
		if (ImGui::CollapsingHeader("Assets##ContentBrowserPanel", ImGuiTreeNodeFlags_DefaultOpen))
		{
			// 点击打开Assets目录
			DirectoryItemFunction(m_pContentBrowser->GetDirectoryTreeRootNode());

			//DrawDirectoryTree(m_ProjectDirectory);
			for (auto& child : m_pContentBrowser->GetDirectoryTreeRootNode().Directories)
			{
				DrawDirectoryTree(child);
			}
			//DrawDirectoryTree(m_DirectoryTreeRootNode);
		}
	}

	void ContentBrowserPanel::DrawDirectoryTree(ContentBrowserDirectory& node)
	{
		ImGuiEx::ScopedID id(node.AbsolutePath.c_str());

		std::string nodeName = ICON_FA_FOLDER;
		nodeName += " ";
		nodeName += node.Name;

		if (ImGui::TreeNodeEx(nodeName.c_str(), node.UIFlags))
		{
			for (auto& child : node.Directories)
			{
				DrawDirectoryTree(child);
			}
			ImGui::TreePop();
		}

		// 点击打开目录
		DirectoryItemFunction(node);
	}

	void ContentBrowserPanel::DirectoryItemFunction(ContentBrowserDirectory& node)
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
		{
			m_pContentBrowser->OpenDirectory(node.AbsolutePath);
		}

	}

	void ContentBrowserPanel::DrawContentBrowser()
	{
		DrawBrowserList();
	}

	//bool ContentBrowserPanel::ImageButton(DLG::ITextureView* view, float width, float height)
	//{
	//	return ImGui::ImageButton((ImTextureID)view, { width, height });
	//}

	void ContentBrowserPanel::DrawBrowserHeader()
	{
		ImGuiEx::ScopedStyleColor colButton(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImVec2 thumbnailSize = { 25.0f,24.0f };

		// 如果是根目录，则不显示返回按钮
		auto result = std::filesystem::relative(m_pContentBrowser->GetCurrentBrowserDirectory(), m_pContentBrowser->GetProjectDirectory());
		if (result != ".")
		{
			if (ImGui::Button(ICON_FA_CHEVRON_CIRCLE_LEFT "##Back", thumbnailSize))
			{
				auto projectDirectory = m_pContentBrowser->GetProjectDirectory();
				auto directory = m_pContentBrowser->GetCurrentBrowserDirectory().parent_path();
				if (Horizon::HFileSystem::ExistsDirectory(directory) && Horizon::HFileSystem::IsSubPath(projectDirectory, directory))
				{
					m_pContentBrowser->OpenDirectory(directory);
				}
			}//ImGui::SameLine();
		}

		//ImGui::Button(ICON_FA_CHEVRON_CIRCLE_RIGHT "##Forward", thumbnailSize);			//ImGui::SameLine();

		// 刷新按钮 Refresh button
		if (ImGui::Button(ICON_FA_REDO "##Refresh", thumbnailSize))
		{
			RefreshDirectory();
		}	//ImGui::SameLine();

		// 路径按钮
		DrawPath(m_pContentBrowser->GetCurrentBrowserDirectory());
	}

	void ContentBrowserPanel::DrawPath(const pfsPath& path)
	{
		ImVec2 thumbnailSize = { 25.0f,24.0f };
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);

		auto projectParentDirectory = m_pContentBrowser->GetProjectDirectory().parent_path();

		size_t pathPos = 0;
		pfsPath relativePath = Horizon::HFileSystem::RelativePath(path, projectParentDirectory);

		std::string pathstr = relativePath.string();

		auto spilt = Horizon::HStringTools::Split(pathstr, "\\");

		for (auto& item : spilt)
		{
			pathPos += item.size() + 1;
			ImVec2 buttonSize = ImVec2(item.size() * thumbnailSize.x * 0.35, thumbnailSize.y);

			if (item == ".")
				continue; // Skip current directory

			if (ImGui::ButtonEx(std::string(item).c_str(), ImVec2(0,0), ImGuiButtonFlags_AlignTextBaseLine))
			{
				m_pContentBrowser->OpenDirectory(projectParentDirectory / pathstr.substr(0, pathPos));
				break;
			}				//ImGui::SameLine();

			//ImGui::Button(ICON_FA_CHEVRON_RIGHT, thumbnailSize);				//ImGui::SameLine();
			ImGui::Text(ICON_FA_CHEVRON_RIGHT);				//ImGui::SameLine();
		}
	}

	//DLG::ITextureView* ContentBrowserPanel::GetFileIcon(HCBDirectoryItem& item)
	//{
	//	return ThumbnailManager::GetInstance().GetFileIcon(item);
	//}

	bool ContentBrowserPanel::ItemFunction(ContentBrowserItem& item)
	{
		//Tool tip
		if (ImGui::IsItemHovered())
		{
			m_IsAnyContentBrowserItemHovered = true;

			ImGui::BeginTooltip();
			ImGui::Text(item.AbsolutePath.string().c_str());
			ImGui::EndTooltip();

			//Click
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				m_pContentBrowser->SelectAll(false);
				item.Selected = true;
			}
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (item.IsDirectory)
				{
					m_pContentBrowser->OpenDirectory(item.AbsolutePath);
					return true;
				}
				else
				{
					AssetEditor::Instance().OpenAsset(item.Path, item.MetaData);
				}
			}
		}

		if (!item.IsDirectory)
			ItemBeginDragSource(item);
		else
			ItemBeginDropTarget(item);

		if (ItemContextMenu(item))
			return true;

		return false;
	}

	void ContentBrowserPanel::ItemBeginDragSource(const ContentBrowserItem& item)
	{
		static std::string itemPath;
		if (ImGui::BeginDragDropSource())
		{
			auto aPath = VFS::GetInstance()->AbsolutePath(Core::GetAssetsPathVFS());
			itemPath = Core::GetAssetsPathVFS() + std::filesystem::relative(item.AbsolutePath, aPath).string();

			ImGui::SetDragDropPayload("PLACE_CONTENT_BROWSER_ITEM", itemPath.c_str(), itemPath.size() + 1);
			ImGui::Text(itemPath.c_str());

			ImGui::EndDragDropSource();
		}
	}

	void ContentBrowserPanel::ItemBeginDropTarget(const ContentBrowserItem& item)
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const auto* payload = ImGui::AcceptDragDropPayload("PLACE_CONTENT_BROWSER_ITEM"))
			{
				std::wstring data = static_cast<wchar_t*>(payload->Data);
				std::wcout << data << std::endl;


				ImGuiEx::PushNotification({ ImGuiExToastType::Info, "Drag file in directory" });
			}
			ImGui::EndDragDropTarget();
		}
	}


	void ContentBrowserPanel::DrawBrowserList()
	{
		m_pContentBrowser->ClearRefreshedFlag();

		ImGuiEx::ScopedStyleColor colButton(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGuiEx::ScopedStyleVar itemSpacing(ImGuiStyleVar_ItemSpacing, ImVec2(4, 8));

		Thumbnial& thumbnial = Thumbnial::Get();

		const ImVec2 windowPos = ImGui::GetWindowPos();
		const ImVec2 windowSize = ImGui::GetWindowSize();
		const ImVec2 windowEndPos = ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y);

		//Calculate column count
		const float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = static_cast<int>(panelWidth / (thumbnial.CellSize));
		if (columnCount < 1)
			columnCount = 1;
		ImGui::Columns(columnCount, 0, false);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		m_IsAnyContentBrowserItemHovered = false;

		auto drawItemFunction = [&, this](ContentBrowserItem& item)
			{
				ImGuiEx::ScopedID imID(&item);

				if (item.Renameing)
					ImGui::InvisibleButton(item.AbsolutePathStr.c_str(), thumbnial.ImageSize);
				else
					ImGui::InvisibleButton(item.AbsolutePathStr.c_str(), thumbnial.Size);

				const ImVec2 p0 = ImGui::GetItemRectMin();
				const ImVec2 p1 = ImVec2(p0.x + thumbnial.Size.x, p0.y + thumbnial.Size.y);

				//Invisible clip
				if (p0.y > windowEndPos.y || p1.y < windowPos.y)
				{
					ImGui::NextColumn();
					return;
				}

				item.iconView = GetFileIcon(item);
				thumbnial.Draw(m_pContentBrowser, draw_list, item, p0, p1);
			};

		// 目录
		for (auto& item : m_pContentBrowser->GetCurrentDirectoryNode().Directories)
		{
			drawItemFunction(item);
			if (m_pContentBrowser->IsRefreshed())
				break;

			ImGuiEx::ScopedID imID(&item);

			if (ItemFunction(item))
				break;

			ImGui::NextColumn();
		}

		// 文件
		for (auto& item : m_pContentBrowser->GetCurrentDirectoryNode().Files)
		{
			drawItemFunction(item);
			if (m_pContentBrowser->IsRefreshed())
				break;

			ImGuiEx::ScopedID imID(&item);

			if (ItemFunction(item))
				break;

			ImGui::NextColumn();
		}

		//ImGui::Columns(1);
		//ImGui::SliderFloat("Thumbnail Size", &thumbnailImageSizeY, 16, 512);
		//ImGui::SliderFloat("Padding", &padding, 0, 32);
	}

	void ContentBrowserPanel::DrawBrowserListItem()
	{
	}

	////////////////////////////////////////////////////////////////
	///		Context	Menu
	////////////////////////////////////////////////////////////////
	bool ContentBrowserPanel::ItemContextMenu(ContentBrowserItem& item)
	{
		return ImGuiEx::PopupContextItem<bool>([this, &item]()
			{
				m_IsAnyContentBrowserItemHovered = true;

				if (ImGui::Selectable(EditorText{ "Rename" }.c_str()))
				{
					item.Renameing = true;
					return true;
				}
				ImGui::Separator();

				if (ImGui::Selectable(EditorText{ "Remove" }.c_str()))
				{
					m_pContentBrowser->DeleteDirectoryItem(item);
					return true;
				}
				ImGui::Separator();

				if (ImGui::Selectable(EditorText{ "Show in Explorer" }.c_str()))
				{
					m_pContentBrowser->ShowInExplorer(item.AbsolutePath.parent_path());
					return true;
				}

				return false;
			});
	}

	void ContentBrowserPanel::ContentBrowserContextMenu(const pfsPath& path)
	{
		if (!m_IsAnyContentBrowserItemHovered && ImGui::BeginPopupContextItem("ContentBrowserContextMenu"))
		{

			if (ImGui::MenuItemEx(EditorText{ "Create Directory" }.c_str(), ICON_FA_FOLDER))
			{
				auto task = ImGuiEx::ImTaskManager::GetInstance().NewTask(
					new Editor::NewDirectoryUITask(path),
					"New Directory"
				);
			}
			//	m_pContentBrowser->CreateNewDirectory(path);

			if (ImGui::MenuItem(EditorText{ "Show in Explorer" }.c_str()))
				m_pContentBrowser->ShowInExplorer(path);

			if (ImGui::MenuItemEx(EditorText{ "Refresh" }.c_str(), ICON_FA_REDO))
				RefreshDirectory();

			if (ImGui::MenuItem(EditorText{ "Copy Path" }.c_str()))
				m_pContentBrowser->CopyPath(path);

			ImGui::Separator();

			EngineAssetFactory factory;
			auto path = VFS::GetResourcePathVFS(m_pContentBrowser->GetCurrentBrowserDirectory().string());

			if (ImGui::MenuItem(EditorText{ "Create Scene" }.c_str()))
			{
				factory.CreateAsset(path, "Scene");
				RefreshDirectory();
			}

			if (ImGui::MenuItem(EditorText{ "Create UI Document" }.c_str()))
			{
				factory.CreateAsset(path, "UIDocument");
				RefreshDirectory();
			}

			if (ImGui::MenuItem(EditorText{ "Create UI Css" }.c_str()))
			{
				factory.CreateAsset(path, "UICss");
				RefreshDirectory();
			}

			if (ImGui::MenuItem(EditorText{ "Create Lua Script" }.c_str()))
			{
				factory.CreateAsset(path, "LuaScript");
				RefreshDirectory();
			}

			if (ImGui::MenuItem(EditorText{ "Create GalGame Story Script" }.c_str()))
			{
				factory.CreateAsset(path, "GalGameStoryScript");
				RefreshDirectory();
			}

			ImGui::EndPopup();
		}

		if (!m_IsAnyContentBrowserItemHovered && ImGui::IsWindowHovered())
		{
			//ImGui::SetTooltip("Right-click to open Content Browser popup");

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImGui::OpenPopup("ContentBrowserContextMenu");
			}
		}
	}

	void* ContentBrowserPanel::GetFileIcon(ContentBrowserItem& item)
	{
		if (item.IsDirectory)
		{
			return m_Icons["Folder"]->GetTexture()->GetShaderResourceView();
		}

		if (item.MetaData.AssetType == "Texture")
		{
			return m_Icons["Image"]->GetTexture()->GetShaderResourceView();
		}

		if (item.MetaData.AssetType == "Sound")
		{
			return m_Icons["Sound"]->GetTexture()->GetShaderResourceView();
		}

		if (item.MetaData.AssetType == "HTML")
		{
			return m_Icons["HTML"]->GetTexture()->GetShaderResourceView();
		}

		if (item.MetaData.AssetType == "CSS")
		{
			return m_Icons["CSS"]->GetTexture()->GetShaderResourceView();
		}

		if (item.MetaData.AssetType == "LuaScript")
		{
			return m_Icons["LuaScript"]->GetTexture()->GetShaderResourceView();
		}

		if (item.MetaData.AssetType == "Scene")
		{
			return m_Icons["Scene"]->GetTexture()->GetShaderResourceView();
		}

		//if (item.Ext == ".png" || item.Ext == ".jpg" || item.Ext == ".bmp" || item.Ext == ".tga")
		//{
		//	return m_Icons["Image"]->GetTexture()->GetShaderResourceView();
		//}

		return m_Icons["File"]->GetTexture()->GetShaderResourceView();
	}

	////////////////////////////////////////////////////////////////
	///		Content	Browser	Function
	////////////////////////////////////////////////////////////////
	void ContentBrowserPanel::RefreshDirectory()
	{
		m_pContentBrowser->RefreshDirectory();
		m_pContentBrowser->RefreshDirectoryTreeRoot();

		for (auto& item : m_pContentBrowser->GetCurrentDirectoryNode().Directories)
		{
			item.iconView = GetFileIcon(item);
		}

		for (auto& item : m_pContentBrowser->GetCurrentDirectoryNode().Files)
		{
			item.iconView = GetFileIcon(item);
		}
	}

}
