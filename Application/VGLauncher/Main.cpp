#include "VGLauncherData.h"
#include "Include/VGLauncher.h"
#include <VGEngine/Include/Core/VFS.h>
#include <VGEngine/Include/Engine/VGEngine.h>
#include <VGEditorFramework/Include/EditorCore/EditorCore.h>
#include <VGPackage/Include/PackageFileSystem.h>

/// @brief 表示启动器虚拟文件系统（VFS）中各类资源和设置的路径。
struct LauncherVFSPath
{
	std::string assets;           // 项目的资源目录路径
	std::string editor;           // 编辑器的资源目录路径
	std::string engine;           // 引擎核心的目录路径
	std::string projectSettings;  // 项目设置文件路径
	std::string projectIntermediate; // 项目中间文件路径
};

/// @brief 初始化虚拟文件系统（VFS）。
/// @param path 路径结构体，包含编辑器和引擎的资源路径。
void InitializeVFS(LauncherVFSPath path)
{
	using namespace VisionGal;

	// 添加编辑器资源虚拟文件系统
	VFS::MountPackageFileSystem(
		Editor::EditorCore::GetEditorResourcePathVFS(),
		"Data/editor.pak",
		path.editor
	);

	// 添加引擎资源虚拟文件系统
	VFS::MountPackageFileSystem(
		Core::GetEngineResourcePathVFS(),
		"Data/engine.pak",
		path.engine
	);
}

/// @brief 程序入口点。Windows平台使用WinMain，其他平台使用main。
#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
	using namespace VisionGal;

	// 获取CMake根目录
	std::string editorProjectRootDir;
#ifdef EDITOR_PROJECT_ROOT_DIR
	std::cout << "Engine Project root is: " << EDITOR_PROJECT_ROOT_DIR << std::endl;
	editorProjectRootDir = EDITOR_PROJECT_ROOT_DIR;
#endif

	// 设置全局为UTF-8模式
	std::locale::global(std::locale(".utf8"));

	// 初始化虚拟文件系统
	LauncherVFSPath paths;
	paths.editor = editorProjectRootDir + "/Resource/Editor/";
	paths.engine = editorProjectRootDir + "/Resource/Engine/";
	InitializeVFS(paths);

	// 加载编辑器配置
	Editor::EditorCore::LoadEditorPreferences();
	// 加载启动器数据
	Editor::VGLauncherData::LoadLauncherData();

	// 初始化启动器
	Ref<Editor::VGLauncher> editor = CreateRef<Editor::VGLauncher>();
	editor->Initialize();
	VGEngine::Get()->AddApplication(editor);

	// 运行引擎
	VGEngine::Get()->Run();
}