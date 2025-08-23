#pragma once
#include "Asset.h"

namespace VisionGal
{
	struct UIDocumentAsset : public VGAsset
	{
		std::string Text;

		UIDocumentAsset()
			: VGAsset("UIDocument")
			//: HAssetBase(HAssetType::Scene)
		{
		}
	};

	class VG_ENGINE_API UIDocumentAssetWriter : public IAssetWriter
	{
	public:
		UIDocumentAssetWriter() = default;
		~UIDocumentAssetWriter() override = default;

		bool Write(const std::string path, VGAsset* asset) override;
	};

	struct UICssAsset : public VGAsset
	{
		std::string Text;

		UICssAsset()
			: VGAsset("UICss")
			//: HAssetBase(HAssetType::Scene)
		{
		}
	};

	class VG_ENGINE_API UICssAssetWriter : public IAssetWriter
	{
	public:
		UICssAssetWriter() = default;
		~UICssAssetWriter() override = default;

		bool Write(const std::string path, VGAsset* asset) override;
	};
}