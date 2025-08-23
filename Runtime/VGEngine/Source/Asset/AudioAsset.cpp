#include "Asset/AudioAsset.h"

namespace VisionGal
{
	bool AudioAssetLoader::Read(const std::string path, Ref<VGAsset>& asset)
	{
		auto videoAsset = CreateRef<AudioAsset>();
		videoAsset->audioClip = CreateRef<AudioClip>();

		if (videoAsset->audioClip->Open(path))
		{
			asset = videoAsset;
			return true;
		}

		return false;
	}
}