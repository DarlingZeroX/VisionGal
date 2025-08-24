// Copyright (c) 2025 梦旅缘心
// This file is part of VisionGal and is licensed under the MIT License.
// For the latest information, see https://github.com/DarlingZeroX/VisionGal
// See the LICENSE file in the project root for details.

#pragma once
#include "../../EngineConfig.h"
#include "../../Core/Core.h"
#include "../../Asset/TextureAsset.h"
#include <unordered_set>
#include <HCore/Include/Core/HTypeInfo.h>
#include <HCore/Include/System/HFileSystem.h>

namespace VisionGal
{
	class VG_ENGINE_API AssetManager
	{
		AssetManager();
	public:
		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		AssetManager(AssetManager&&) noexcept = default;
		AssetManager& operator=(AssetManager&&) noexcept = default;
		~AssetManager() = default;

		static AssetManager* GetInstance();

		/// 模板方法加载资产
		/// @param path 资产路径
		/// @param cache 是否缓存资产
		/// @return 资产引用
		template<class T>
		Ref<T> LoadAsset(const String& path, bool cache = true)
		{
			return std::dynamic_pointer_cast<T>(LoadAsset(typeid(T), path, cache));
		}
		/// 检查是否存在加载器
		/// @return 加载器引用
		template<class T>
		Ref<T> ExistLoader()
		{
			return std::dynamic_pointer_cast<T>(ExistLoader(typeid(T)));
		}
		/// @return 加载器是否存在
		/// @param typeInfo 资产类型
		/// @return 加载器是否存在
		bool ExistLoader(const type_info& typeInfo);

		/// 检查资产是否过期
		/// @param path 资产路径
		/// @return 资产是否过期
		bool IsExpiredAsset(const String& path);
		/// 加载资产
		/// @param typeInfo 资产类型
		/// @param path 资产路径
		/// @param cache 是否缓存资产
		/// @return 资产引用
		Ref<VGAsset> LoadAsset(const type_info& typeInfo, const String& path, bool cache = true);
		/// 移除资产
		/// @param path 资产路径
		/// @return 是否成功移除资产
		bool RemoveAsset(const String& path);
		/// 检查资产是否存在
		/// @param path 资产路径
		/// @return 资产是否存在
		bool ExistsAsset(const String& path);

		/// @return 缓存资产数量
		size_t NumCacheAsset();
		/// 移除缓存资产
		/// @param path 资产路径
		/// @return 是否成功移除缓存资产
		bool RemoveCachedAsset(const String& path);

		/// 注册资产加载器
		/// @param typeInfo 资产类型
		/// @param loader 资产加载器
		/// @return 是否成功注册资产加载器
		bool RegisterAssetLoader(const type_info& typeInfo, IAssetLoader* loader);
	private:
		std::time_t GetCFTime(std::filesystem::file_time_type type );

		struct CacheAsset
		{
			String Path;
			Ref<VGAsset> Asset;
			std::filesystem::file_time_type LastWriteTime;
			bool HasLastWriteTime = false;
		};

		// 缓存资产
		std::unordered_map<String, CacheAsset> m_AssetMap;
		// 资产加载器
		Horizon::unordered_type_map<Scope<IAssetLoader>>  m_AssetLoaders;
		// 加载列表
		std::unordered_set<String> m_LoadingAssets;

		// 读取锁
		std::mutex m_ReadMutex;
		std::condition_variable m_LoadingCV;
	};
	
}