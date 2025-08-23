#include "Include/EngineEditor.h"
#include "Include/EditorInitializer.h"
#include <HCore/Include/System/HFileSystem.h>
#include <VGEngine/Include/Engine/VGEngine.h>

int main(int argc, char* argv[])
{
	using namespace VisionGal;

	// 获取编辑器项目根目录
	std::string editorProjectRootDir;
#ifdef EDITOR_PROJECT_ROOT_DIR
	std::cout << "VisionGal Project root is: " << EDITOR_PROJECT_ROOT_DIR << std::endl;
	editorProjectRootDir = EDITOR_PROJECT_ROOT_DIR;
#endif

	// 设置全局为UTF-8模式
	std::locale::global(std::locale(".utf8"));  // C++标准库使用UTF-8

	// 加载编辑器配置
	Editor::EditorCore::LoadEditorPreferences();

	// 读取项目根目录
	std::string projectRootDir = editorProjectRootDir + "/Projects/Test Project";
	std::string projectPath;
	if (Horizon::HFileSystem::ReadTextFromFile("Data/EditorStartupData.txt", projectPath))
		projectRootDir = projectPath;

	// 检查项目目录是否存在
	if (!EditorInitializer::CheckProjectRootDir(projectRootDir))
		return -1;

	// 初始化文件系统
	EditorVFSPath paths;
	paths.assets = projectRootDir + "/Assets/";
	paths.projectSettings = projectRootDir + "/ProjectSettings/";
	paths.projectIntermediate = projectRootDir + "/Intermediate/";
	paths.editor = editorProjectRootDir + "/Resource/Editor/";
	paths.engine = editorProjectRootDir + "/Resource/Engine/";
	EditorInitializer::InitializeVFS(paths);

	// 加载项目
	VGEngine::Get()->LoadProject();

	// 初始化编辑器应用
	Ref<Editor::VGEditorApplication> editor = CreateRef<Editor::VGEditorApplication>();
	editor->Initialize();
	editor->InitializeEditorPanels();
	VGEngine::Get()->AddApplication(editor);

	// 加载编辑器主场景
	VGEngine::Get()->LoadEditorMainScene();

	// 运行引擎主循环
	VGEngine::Get()->Run();
}