#pragma once
#include "Texture2D.h"
#include "Video.h"
#include "../Interface/Loader.h"
#include <HCore/Include/Core/HSingleton.h>

namespace VisionGal {

	class VG_ENGINE_API TextureResourceManager : public Horizon::HSingletonBase<TextureResourceManager>, public VGObjectLoader
	{
	public:
		TextureResourceManager();
		TextureResourceManager(const TextureResourceManager&) = default;
		TextureResourceManager& operator=(const TextureResourceManager&) = default;
		TextureResourceManager(TextureResourceManager&&) noexcept = default;
		TextureResourceManager& operator=(TextureResourceManager&&) noexcept = default;
		~TextureResourceManager() override = default;

		static void CreateManager();
		uint64 NumCacheTexture() const { return m_CachedTextures.size(); }
		VGObjectPtr StaticLoadObject(const String& path) override;

	private:
		std::unordered_map<String, Ref<Texture2D>> m_CachedTextures;
	};


	class VG_ENGINE_API VideoResourceManager : public Horizon::HSingletonBase<VideoResourceManager>, public VGObjectLoader
	{
	public:
		VideoResourceManager();
		VideoResourceManager(const VideoResourceManager&) = default;
		VideoResourceManager& operator=(const VideoResourceManager&) = default;
		VideoResourceManager(VideoResourceManager&&) noexcept = default;
		VideoResourceManager& operator=(VideoResourceManager&&) noexcept = default;
		~VideoResourceManager() override = default;

		static void CreateManager();
		//uint64 NumCacheTexture() const { return m_CachedVideos.size(); }
		VGObjectPtr StaticLoadObject(const String& path) override;

	private:
		//std::unordered_map<String, Ref<VideoClip>> m_CachedVideos;
	};

	class VG_ENGINE_API AudioResourceManager : public Horizon::HSingletonBase<AudioResourceManager>, public VGObjectLoader
	{
	public:
		AudioResourceManager();
		AudioResourceManager(const AudioResourceManager&) = default;
		AudioResourceManager& operator=(const AudioResourceManager&) = default;
		AudioResourceManager(AudioResourceManager&&) noexcept = default;
		AudioResourceManager& operator=(AudioResourceManager&&) noexcept = default;
		~AudioResourceManager() override = default;

		static void CreateManager();
		VGObjectPtr StaticLoadObject(const String& path) override;
	};

	VG_ENGINE_API void CreateResourceManagers();
}