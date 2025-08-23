#pragma once
#include "Asset.h"
#include "../Core/Core.h"
#include "../Resource/Audio.h"

namespace VisionGal
{
	struct AudioAsset : public VGAsset
	{
		AudioAsset()
			: VGAsset("Audio")
		{
		}

		Ref<AudioClip> audioClip;
	};

	class VG_ENGINE_API AudioAssetLoader : public IAssetLoader
	{
	public:
		AudioAssetLoader() = default;
		~AudioAssetLoader() override = default;
	
		bool Read(const std::string path, Ref<VGAsset>& asset) override;
	};

}
