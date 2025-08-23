#pragma once
#include <string>
#include <VGEditorFramework/Include/EditorCore/EditorCore.h>

struct VGDesktopApplicationVFSPath
{
	std::string assets;
	std::string editor;
	std::string engine;
	std::string projectSettings;
	std::string projectIntermediate;
};

struct VGDesktopApplicationInitializer
{
	static void PakResource(const VGDesktopApplicationVFSPath& path);

	static void InitializeVFS(const VGDesktopApplicationVFSPath& path);
};

