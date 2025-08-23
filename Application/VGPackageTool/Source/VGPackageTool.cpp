#include "VGPackageTool.h"
#include "VGPackage/Include/PakReader.h"
#include "VGPackage/Include/PakWriter.h"
#include <VGEngine/Include/Core/Core.h>
#include <VGEngine/Include/Core/VFS.h>
#include <VGEditorFramework/Include/EditorCore/EditorCore.h>
#include "HCore/Include/System/HFileSystem.h"

namespace VisionGal::Editor
{
	void VGPackageTool::TestPackage()
	{
		PakFileReader reader;
		PakFileWriter writer;

		String engineResourcePath = VFS::GetInstance()->AbsolutePath(Core::GetEngineResourcePathVFS());
		String editorResourcePath = VFS::GetInstance()->AbsolutePath(EditorCore::GetEditorResourcePathVFS());

		Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data");
		writer.WriteDirectoryToPakFile(engineResourcePath, "Data/engine.pak", "");
		writer.WriteDirectoryToPakFile(editorResourcePath, "Data/editor.pak", "");

		reader.ReadPakFile("Data/engine.pak", "Data/engine", "");
		reader.ReadPakFile("Data/editor.pak", "Data/editor", "");
	}

	void VGPackageTool::PakEngineEditorResources()
	{	PakFileReader reader;
		PakFileWriter writer;
		String engineResourcePath = VFS::GetInstance()->AbsolutePath(Core::GetEngineResourcePathVFS());
		String editorResourcePath = VFS::GetInstance()->AbsolutePath(EditorCore::GetEditorResourcePathVFS());

		Horizon::HFileSystem::CreateDirectoryWhenNoExist("Data");

		writer.WriteDirectoryToPakFile(engineResourcePath, "Data/engine.pak", "");
		writer.WriteDirectoryToPakFile(editorResourcePath, "Data/editor.pak", "");
	}
}
