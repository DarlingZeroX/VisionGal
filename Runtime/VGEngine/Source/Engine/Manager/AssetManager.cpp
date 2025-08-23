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

		// 第一阶段：检查缓存或等待加载
		{
			std::unique_lock<std::mutex> lock(m_ReadMutex);

			// 先从缓存中查找资产
			auto it = m_AssetMap.find(path);
			if (it != m_AssetMap.end())
			{
				asset = it->second;
				return asset;
			}

			// 如果正在加载，等待完成
			if (m_LoadingAssets.find(path) != m_LoadingAssets.end())
			{
				m_LoadingCV.wait(lock, [this, &path] {
					return m_LoadingAssets.find(path) == m_LoadingAssets.end();
					});

				// 等待后再次检查缓存
				it = m_AssetMap.find(path);
				if (it != m_AssetMap.end())
				{
					asset = it->second;
					return asset;
				}
			}

			// 标记资源正在加载
			m_LoadingAssets.insert(path);
		}

		// 第二阶段：加载资源（不在锁的保护下）
		bool loadSuccessful = false;
		try {
			// 找到资产访问器
			auto loader = m_AssetLoaders.find(&typeInfo);
			if (loader == m_AssetLoaders.end()) {
				throw std::runtime_error("Asset loader not found");
			}

			// 读取资产
			loader->second->Read(path, asset);
			loadSuccessful = (asset != nullptr);
		}
		catch (...) {
			loadSuccessful = false;
			// 异常会在后续释放锁时处理
		}

		// 第三阶段：更新缓存并通知等待者
		{
			std::lock_guard<std::mutex> lock(m_ReadMutex);

			// 从加载列表中移除
			m_LoadingAssets.erase(path);

			// 如果加载成功且缓存中没有该资源，则添加到缓存
			if (cache && loadSuccessful && m_AssetMap.find(path) == m_AssetMap.end()) {
				m_AssetMap[path] = asset;
			}

			// 通知所有等待者资源状态已更新
			m_LoadingCV.notify_all();
		}

		return asset;
	}
	/*
	Ref<VGAsset> AssetManager::LoadAsset(const type_info& typeInfo, String path)
	{
		Ref<VGAsset> asset = nullptr;
		std::lock_guard<std::mutex> lock(m_ReadMutex);

		// 先从缓存中查找资产
		if (m_AssetMap.find(path) != m_AssetMap.end())
		{
			asset = m_AssetMap[path];
			return asset;
		}

		// 是否正在加载
		while (m_LoadingAssets.find(path) != m_LoadingAssets.end())
		{
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}

		m_LoadingAssets.insert(path);

		// 找到资产访问器 Find reader
		auto loader = m_AssetLoaders.find(&typeInfo);
		if (loader == m_AssetLoaders.end())
		{
			return nullptr;
		}

		// 读取资产
		loader->second->Read(path, asset);

		// 缓存资产
		if (asset != nullptr)
			m_AssetMap[path] = asset;

		// 从加载列表删除
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
