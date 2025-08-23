#pragma once
#include "Asset.h"
#include "../Scene/Scene.h"

namespace VisionGal
{
	struct SceneAsset : public VGAsset
	{
		Ref<Scene> LoadedScene = nullptr;
		Scene* WriteScene = nullptr;

		SceneAsset()
			: VGAsset("Scene")
			//: HAssetBase(HAssetType::Scene)
		{}
	};
}