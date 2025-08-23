#include "Engine/Manager/AssetManager.h"
#include "Asset/TextureAsset.h"
#include "Asset/VideoAsset.h"
#include <time.h>

#include "Asset/AudioAsset.h"
#include "Core/VFS.h"
#include "HCore/Include/System/HFileSystem.h"

namespace VisionGal
{
	AssetManager::AssetManager()
	{
		RegisterAssetLoader(typeid(TextureAsset), new TextureAssetLoader());
		RegisterAssetLoader(typeid(VideoAsset), new VideoAssetLoader());
		RegisterAssetLoader(typeid(AudioAsset), new AudioAssetLoader());
	}

	AssetManager* AssetManager::Get()
	{
		static AssetManager manager;

		return &manager;
	}


	bool AssetManager::ExistLoader(const type_info& typeInfo)
	{
		return m_AssetLoaders.find(&typeInfo) != m_AssetLoaders.end();
	}
	
	Ref<VGAsset> AssetManager::LoadAsset(const type_info& typeInfo, String path, bool cache)
	{
		Ref<VGAsset> asset = nullptr;

		// ��һ�׶Σ���黺���ȴ�����
		{
			std::unique_lock<std::mutex> lock(m_ReadMutex);

			// �ȴӻ����в����ʲ�
			auto it = m_AssetMap.find(path);
			if (it != m_AssetMap.end())
			{
				asset = it->second;
				return asset;
			}

			// ������ڼ��أ��ȴ����
			if (m_LoadingAssets.find(path) != m_LoadingAssets.end())
			{
				m_LoadingCV.wait(lock, [this, &path] {
					return m_LoadingAssets.find(path) == m_LoadingAssets.end();
					});

				// �ȴ����ٴμ�黺��
				it = m_AssetMap.find(path);
				if (it != m_AssetMap.end())
				{
					asset = it->second;
					return asset;
				}
			}

			// �����Դ���ڼ���
			m_LoadingAssets.insert(path);
		}

		// �ڶ��׶Σ�������Դ���������ı����£�
		bool loadSuccessful = false;
		try {
			// �ҵ��ʲ�������
			auto loader = m_AssetLoaders.find(&typeInfo);
			if (loader == m_AssetLoaders.end()) {
				throw std::runtime_error("Asset loader not found");
			}

			// ��ȡ�ʲ�
			loader->second->Read(path, asset);
			loadSuccessful = (asset != nullptr);
		}
		catch (...) {
			loadSuccessful = false;
			// �쳣���ں����ͷ���ʱ����
		}

		// �����׶Σ����»��沢֪ͨ�ȴ���
		{
			std::lock_guard<std::mutex> lock(m_ReadMutex);

			// �Ӽ����б����Ƴ�
			m_LoadingAssets.erase(path);

			// ������سɹ��һ�����û�и���Դ������ӵ�����
			if (cache && loadSuccessful && m_AssetMap.find(path) == m_AssetMap.end()) {
				m_AssetMap[path] = asset;
			}

			// ֪ͨ���еȴ�����Դ״̬�Ѹ���
			m_LoadingCV.notify_all();
		}

		return asset;
	}
	/*
	Ref<VGAsset> AssetManager::LoadAsset(const type_info& typeInfo, String path)
	{
		Ref<VGAsset> asset = nullptr;
		std::lock_guard<std::mutex> lock(m_ReadMutex);

		// �ȴӻ����в����ʲ�
		if (m_AssetMap.find(path) != m_AssetMap.end())
		{
			asset = m_AssetMap[path];
			return asset;
		}

		// �Ƿ����ڼ���
		while (m_LoadingAssets.find(path) != m_LoadingAssets.end())
		{
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}

		m_LoadingAssets.insert(path);

		// �ҵ��ʲ������� Find reader
		auto loader = m_AssetLoaders.find(&typeInfo);
		if (loader == m_AssetLoaders.end())
		{
			return nullptr;
		}

		// ��ȡ�ʲ�
		loader->second->Read(path, asset);

		// �����ʲ�
		if (asset != nullptr)
			m_AssetMap[path] = asset;

		// �Ӽ����б�ɾ��
		m_LoadingAssets.erase(path);

		return asset;
	}*/

	bool AssetManager::RemoveAsset(const String& path)
	{
		if (auto result = m_AssetMap.find(path); result != m_AssetMap.end())
		{
			m_AssetMap.erase(path);
		}

		auto aPath = VFS::GetInstance()->AbsolutePath(path);

		// remove data file
		Horizon::HFileSystem::RemoveFile(aPath);

		// remove meta file
		auto metaPath = aPath + ".meta";
		Horizon::HFileSystem::RemoveFile(metaPath);

		return true;
	}

	bool AssetManager::ExistsAsset(const String& path)
	{
		return false;
	}

	size_t AssetManager::NumCacheAsset()
	{
		return m_AssetMap.size();
	}

	bool AssetManager::RemoveCachedAsset(const String& path)
	{
		std::lock_guard guard(m_ReadMutex);

		if (m_AssetMap.find(path) != m_AssetMap.end())
		{
			m_AssetMap.erase(path);
			return true;
		}

		return false;
	}

	bool AssetManager::RegisterAssetLoader(const type_info& typeInfo, IAssetLoader* loader)
	{
		m_AssetLoaders[&typeInfo] = std::unique_ptr<IAssetLoader>(loader);

		return true;
	}
}
