#pragma once
#include <string>
#include <VGEditorFramework/Include/EditorCore/EditorCore.h>

struct EditorVFSPath
{
	std::string assets;
	std::string editor;
	std::string engine;
	std::string projectSettings;
	std::string projectIntermediate;
};

struct EditorInitializer
{
	static bool CheckProjectRootDir(const std::string& projectRootDir);

	static void PakResource(const EditorVFSPath& path);

	static void InitializeVFS(const EditorVFSPath& path);
};

