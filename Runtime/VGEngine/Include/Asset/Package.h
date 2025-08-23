#pragma once
#include "../EngineConfig.h"
#include "../Core/Core.h"
#include "Asset.h"
#include <fstream>

namespace VisionGal
{
	struct VG_ENGINE_API VGPackage
	{
		VGPackage() = default;
		VGPackage(const String& path);
		~VGPackage() = default;

		static Ref<VGPackage> NewPackage(const String& path);
		static Ref<VGPackage> LoadPackage(const String& path);

		static bool CheckPackageValid(const String& path);

		String GetAssetPath();
		//HJson& GetMetaJson() { return m_AssetMetaJson; };
		std::fstream& GetBinaryStream() { return m_AssetBinaryDataFile; }
		VGAssetMetaData GetMeatData();
		static bool GetMeatData(const String& path, VGAssetMetaData& metadata);
	public:
		void SetAssetType(const String& type);
		void SetAsset(VGAsset* asset);

		void OpenWriteStream();
		void CloseWriteStream();

		void OpenReadStream(VGAsset& assetBase);
		void CloseReadStream();

		bool WriteMetaData(const String& data);

		void ReadAsset(VGAsset& assetBase);

		void OpenReadMetaStream();
		void CloseReadMetaStream();

		String GetPhysicalDataFilePath() { return m_PhysicalDataFilePath; }
	private:
		bool Load();

		String m_VirtualMetaFilePath;
		String m_VirtualDataFilePath;

		//pfsPath m_PhysicalFilePath;
		String m_PhysicalMetaFilePath;
		String m_PhysicalDataFilePath;

		VGAssetMetaData m_AssetMetaData;

		std::fstream m_AssetBinaryDataFile;

		//std::stringstream m_MetaStream;
		//vfspp::IFilePtr m_OutMetaFile;

	};
}


