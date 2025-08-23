#include "pch.h"
#include "Utils/HFileSystemGenerator.h"
#include "Utils/HStringGenerator.h"

namespace Horizon
{
	fsPath HSequenceGenerator::GenerateDirectory(const fsPath& path)
	{
		HSequenceWStringGenerator gen(path);

		auto nextPath = gen.GetNext();
		while (HFileSystem::ExistsDirectory(nextPath))
		{
			nextPath = gen.GetNext();
		}

		HFileSystem::CreateDirectory(nextPath);

		return nextPath;
	}

	fsPath HSequenceGenerator::GenerateAsset(const fsPath& path, const std::wstring& name)
	{
		HSequenceWStringGenerator gen(name);

		auto nextName = gen.GetNext();
		auto fullPath = path / (nextName + L".hasset");
		while (HFileSystem::ExistsDirectory(fullPath))
		{
			nextName = gen.GetNext();
			fullPath = path / (nextName + L".hasset");
		}

		HFileSystem::CreateNullFile(fullPath);

		return fullPath;
	}

	std::wstring HSequenceGenerator::GenerateAssetName(HPath path, std::wstring name)
	{
		HSequenceWStringGenerator gen(name);
		//auto fullPath = HVirtualFileSystem::HPathToPfsPath(path / name).wstring() + L".hasset";

		std::wstring nextName = name;
		//while (HFileSystem::FileExists(fullPath))
		//{
		//	nextName = gen.GetNext();
		//
		//	fullPath = HVirtualFileSystem::HPathToPfsPath(path / nextName).wstring() + L".hasset";
		//}

		return nextName;
	}

	
}
