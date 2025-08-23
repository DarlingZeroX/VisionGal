#pragma once
#include "../Config.h"
#include "../EditorCore/ContentBrowser.h"
#include <VGEngine\Include\Core\Core.h>

namespace VisionGal::Editor {

	struct EditorFileSystemFile
	{
		bool selected = false;
		bool renameing = false;

		std::string ext;
		std::string filename;
		std::string pathStr;
		Horizon::fsPath path;

		Horizon::HAssetMeatData metaData;
		std::string assetType;
		int uiFlags;
	};

	struct EditorFileSystemDirectory
	{
		bool selected = false;

		std::string name;
		int uiFlags;
		Horizon::fsPath path;
		bool needOpen = true;

		std::vector<EditorFileSystemDirectory> Directories;
		std::vector<EditorFileSystemFile> Files;
	};

	class VG_EDITOR_FRAMEWORK_API EditorFileSystem
	{
	public:
		using pfsPath = Horizon::fsPath;

		EditorFileSystem(const pfsPath& path);

		void OpenRootDirectory();
		void RefreshDirectoryFile(EditorFileSystemDirectory& node);
		EditorFileSystemDirectory& GetRootNode() { return m_RootNode; }
	private:
		EditorFileSystemDirectory m_RootNode;	// 根目录节点
		pfsPath m_ProjectDirectory;
		pfsPath m_CurrentDirectoryOrFile;
	};

	class VG_EDITOR_FRAMEWORK_API FileSystemPanel : public IPanel
	{
	public:
		FileSystemPanel();
		FileSystemPanel(const String& contentPath);
		FileSystemPanel(const FileSystemPanel&) = delete;
		FileSystemPanel& operator=(const FileSystemPanel&) = delete;
		FileSystemPanel(FileSystemPanel&&) noexcept = default;
		FileSystemPanel& operator=(FileSystemPanel&&) noexcept = default;
		~FileSystemPanel() override = default;

		void OnGUI() override;
	private:
		void DrawContentBrowser();
		void DrawDirectoryTree(EditorFileSystemDirectory& node);
		void DrawFile(EditorFileSystemFile& file);
	private:
		Horizon::fsPath m_ContentPath;
		ContentBrowser* m_pContentBrowser;
		Ref<EditorFileSystem> m_EditorContentBrowser;
	};
}