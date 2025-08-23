#pragma once
#include "../Config.h"
#include "EditorComponents/PanelInterface.h"
#include <HCore/Include/System/HFileSystem.h>
#include <VGEngine/Include/Core/Core.h>
#include <HCore/Include/Asset/HAsset.h>
#include <VGEngine/Include/Asset/Package.h>

namespace VisionGal::Editor
{
	struct VG_EDITOR_FRAMEWORK_API AssetEditor
	{
		void OpenAsset(const VGPath& path, const VGAssetMetaData& metaData);

		void RegisterHandler(std::string type, std::function<void(const VGPath&)> handle);

		static AssetEditor& Instance();

		void OpenTextFile(const VGPath& path);
	private:
		std::unordered_map<std::string, std::function<void(const VGPath&)>> m_Handlers;
	};

}
