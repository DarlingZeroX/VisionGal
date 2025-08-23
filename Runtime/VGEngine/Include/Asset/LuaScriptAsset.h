#pragma once
#include "Asset.h"

namespace VisionGal
{
	struct LuaScriptAsset : public VGAsset
	{
		std::string Text;

		LuaScriptAsset()
			: VGAsset("LuaScript")
		{
		}
	};

	class VG_ENGINE_API LuaScriptAssetWriter : public IAssetWriter
	{
	public:
		LuaScriptAssetWriter() = default;
		~LuaScriptAssetWriter() override = default;

		bool Write(const std::string path, VGAsset* asset) override;
	};

}