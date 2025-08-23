#pragma once
#include <string>
#include "../System/HFileSystem.h"

namespace Horizon
{
	struct CORE_MODULE_API HSequenceGenerator
	{
		static fsPath GenerateDirectory(const fsPath& path);
		static fsPath GenerateAsset(const fsPath& path, const std::wstring& name);
		static std::wstring GenerateAssetName(HPath path, std::wstring name);
	};
}
