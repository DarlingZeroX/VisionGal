#pragma once
#include "../Asset.h"
#include "../SceneAsset.h"
#include "../../Core/Core.h"

namespace VisionGal
{
    class VG_ENGINE_API SceneAssetLoader : public IAssetLoader
    {
    public:
        SceneAssetLoader() = default;
        ~SceneAssetLoader() override = default;

        bool Read(const std::string path, Ref<VGAsset>& asset) override;
    };

    class VG_ENGINE_API SceneAssetWriter : public IAssetWriter
    {
    public:
        SceneAssetWriter() = default;
        ~SceneAssetWriter() override = default;

        bool Write(const std::string path, VGAsset* asset) override;
    };
}