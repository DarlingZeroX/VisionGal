#include "Asset/GalGameAsset.h"
#include "Asset/Package.h"
#include "Core/VFS.h"

namespace VisionGal
{
	bool GalGameStoryScriptAssetWriter::Write(const std::string path, VGAsset* asset)
	{
		if (asset == nullptr)
			return false;

		GalGameStoryScriptAsset* uiAsset = dynamic_cast<GalGameStoryScriptAsset*>(asset);

		if (uiAsset == nullptr)
			return false;

		// 创建或打开一个文件用于写入
		if (VFS::WriteTextToFile(path, uiAsset->Text) == false)
			return false;

		// 写入元信息
		auto package = VGPackage::NewPackage(path);
		package->SetAsset(uiAsset);
		package->WriteMetaData("");

		return true;
	}
}
