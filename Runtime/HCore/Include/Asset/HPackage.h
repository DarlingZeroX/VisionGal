// Copyright (c) 2025 梦旅缘心
// This file is part of VisionGal and is licensed under the MIT License.
// See the LICENSE file in the project root for details.

#pragma once
#include "HAsset.h"
#include "../CoreModuleDefinitions.h"
#include "../File/HJson.h"

namespace Horizon
{
	struct CORE_MODULE_API HPackage
	{
		HPackage() = default;

		HPackage(HPath path);

		~HPackage() = default;

		static bool GetMeatData(const HPath& path, HAssetMeatData& metadata);

		static Ref<HPackage> NewPackage(const HPath& path);

		static Ref<HPackage> LoadPackage(const HPath& path, HResult& result);

		static bool CheckPackageValid(const HPath& path);

		fsPath GetAssetPath();

		HJson& GetMetaJson() { return m_AssetMetaJson; };

		std::fstream& GetBinaryStream() { return m_AssetBinaryDataFile; }

		HAssetMeatData GetMeatData();

	public:
		void SetAssetType(std::string type);

		void SetAsset(HAssetBase& asset);

		void OpenOutputStream();
		void CloseOutputStream();

		void OpenOutputMetaStream();
		void CloseOutputMetaStream();

		void OpenReadStream(HAssetBase& assetBase);
		void CloseReadStream();

		void ReadAsset(HAssetBase& assetBase);

		void OpenReadMetaStream();
		void CloseReadMetaStream();

		fsPath GetPhysicalDataFilePath() { return m_PhysicalDataFilePath; }
	private:
		HResult Load();

		HPath m_VirtualMetaFilePath;
		HPath m_VirtualDataFilePath;

		//pfsPath m_PhysicalFilePath;
		fsPath m_PhysicalMetaFilePath;
		fsPath m_PhysicalDataFilePath;

		HAssetBase m_AssetMetaData;

		std::fstream m_AssetBinaryDataFile;
		//std::fstream m_AssetMetaDataFile;

		HJson m_AssetMetaJson;

	};
}


