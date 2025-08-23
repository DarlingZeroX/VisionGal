#pragma once
#include "Asset.h"

namespace VisionGal
{
	struct GalGameStoryScriptAsset : public VGAsset
	{
		std::string Text;

		GalGameStoryScriptAsset()
			: VGAsset("GalGameStoryScript")
		{
		}
	};

	class VG_ENGINE_API GalGameStoryScriptAssetWriter : public IAssetWriter
	{
	public:
		GalGameStoryScriptAssetWriter() = default;
		~GalGameStoryScriptAssetWriter() override = default;

		bool Write(const std::string path, VGAsset* asset) override;
	};

}