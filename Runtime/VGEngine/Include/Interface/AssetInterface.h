#pragma once
#include "../Asset/Asset.h"
#include "../Core/Core.h"

namespace VisionGal
{
    struct IEngineAssetFactory
    {
        virtual ~IEngineAssetFactory() = default;

        virtual Ref<VGAsset> CreateAsset(const String& path, const String& type) = 0;
    };

    struct IAssetFactoryInstance
    {
        virtual ~IAssetFactoryInstance() = default;

        virtual std::string GetFactoryType() = 0;
        virtual Ref<VGAsset> CreateAsset(const String& path) = 0;

        static VGPath GenerateAssetPath(const VGPath& path, const std::string& name, const std::string& ext);
    };
}