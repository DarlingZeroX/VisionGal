#include "ApplicationInitializer.h"
#include <HCore/Include/System/HFileSystem.h>
#include <HCore/Include/Platform/NativeFileDialog/portable-file-dialogs.h>
#include <VGPackage/Include/PakWriter.h>
#include <VGEngine/Include/Core/Core.h>
#include <VGEngine/Include/Core/VFS.h>

void VGDesktopApplicationInitializer::PakResource(const VGDesktopApplicationVFSPath& path)
{
	using namespace VisionGal;

	PakFileWriter writer;

	Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data");

	if (Horizon::HFileSystem::ExistsFile("Data/engine.pak") == false)
		writer.WriteDirectoryToPakFile(path.engine, "Data/engine.pak", "");

	if (Horizon::HFileSystem::ExistsFile("Data/editor.pak") == false)
		writer.WriteDirectoryToPakFile(path.editor, "Data/editor.pak", "");
}

void VGDesktopApplicationInitializer::InitializeVFS(const VGDesktopApplicationVFSPath& path)
{
	using namespace VisionGal;

	//PakResource(path);

	auto& vfs = VFS::GetInstance();

	// 添加引擎资源虚拟文件系统
	VFS::MountPackageFileSystem(
		Core::GetEngineResourcePathVFS(),
		"Data/engine.pak",
		path.engine
	);

	// 添加游戏资产虚拟文件系统
	VFS::MountPackageFileSystem(
		Core::GetAssetsPathVFS(),
		"Data/assets.pak",
		path.assets
	);

	// 添加项目设置虚拟文件系统
	VFS::MountPackageFileSystem(
		Core::GetProjectSettingsPathVFS(),
		"Data/projectSetting.pak",
		path.projectSettings
	);

	auto projectIntermediateFS = std::make_unique<vfspp::NativeFileSystem>(path.projectIntermediate);
	projectIntermediateFS->Initialize();
	vfs->AddFileSystem(Core::GetProjectIntermediatePathVFS(), std::move(projectIntermediateFS));

	auto editorPath = VFS::GetInstance()->AbsolutePath(Editor::EditorCore::GetEditorResourcePathVFS());
	H_LOG_INFO("Editor resource path: %s", editorPath.c_str());

	auto enginePath = VFS::GetInstance()->AbsolutePath(Core::GetEngineResourcePathVFS());
	H_LOG_INFO("Engine resource path: %s", enginePath.c_str());

	auto assetsPath = VFS::GetInstance()->AbsolutePath(Core::GetAssetsPathVFS());
	H_LOG_INFO("Assets resource: %s", assetsPath.c_str());

	auto projectSettingsPath = VFS::GetInstance()->AbsolutePath(Core::GetProjectSettingsPathVFS());
	H_LOG_INFO("Project settings resource path: %s", projectSettingsPath.c_str());

	auto projectIntermediatePath = VFS::GetInstance()->AbsolutePath(Core::GetProjectIntermediatePathVFS());
	H_LOG_INFO("Project intermediate path: %s", projectIntermediatePath.c_str());
}
