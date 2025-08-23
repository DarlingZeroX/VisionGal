#pragma once
#include "../../EngineConfig.h"
#include "../../Core/Core.h"
#include "../../Asset/TextureAsset.h"
#include <unordered_set>
#include <HCore/Include/Core/HTypeInfo.h>

namespace VisionGal
{
	 
	class VG_ENGINE_API AssetManager
	{
		AssetManager();
	public:
		~AssetManager() = default;

		static AssetManager* Get();

		template<class T>
		Ref<T> LoadAsset(String path, bool cache = true)
		{
			return std::dynamic_pointer_cast<T>(LoadAsset(typeid(T), path, cache));
		}

		template<class T>
		Ref<T> ExistLoader()
		{
			return std::dynamic_pointer_cast<T>(ExistLoader(typeid(T)));
		}

		bool ExistLoader(const type_info& typeInfo);
		Ref<VGAsset> LoadAsset(const type_info& typeInfo, String path, bool cache = true);
		bool RemoveAsset(const String& path);
		bool ExistsAsset(const String& path);
		size_t NumCacheAsset();

		bool RemoveCachedAsset(const String& path);

		bool RegisterAssetLoader(const type_info& typeInfo, IAssetLoader* loader);
	private:
		// 缓存资产
		std::unordered_map<String, Ref<VGAsset>> m_AssetMap;
		// 资产加载器
		Horizon::unordered_type_map<Scope<IAssetLoader>>  m_AssetLoaders;
		// 读取锁
		std::mutex m_ReadMutex;
		// 加载列表
		std::unordered_set<std::string> m_LoadingAssets;

		std::condition_variable m_LoadingCV;
	};
	
}