#include "Resource/ResourceManager.h"
#include "Engine/Manager.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Asset/TextureAsset.h"
#include "Asset/VideoAsset.h"
#include "Asset/AudioAsset.h"

namespace VisionGal
{
	TextureResourceManager::TextureResourceManager()
	{
		RegisterObjectLoader(typeid(Texture2D), this);
	}

	void TextureResourceManager::CreateManager()
	{
		if (GetInstanceValid() == true)
			return;

		new TextureResourceManager();
	}

	Ref<Texture2D> CreateRenderTexture(TextureAsset& asset)
	{
		VGFX::TextureDesc desc;
		desc.Width = asset.Width;
		desc.Height = asset.Height;

		desc.Data = asset.Data;
		desc.DataSize = desc.Width * desc.Height * 4;
		desc.Type = GL_UNSIGNED_BYTE;

		if (asset.Format == ImageFormat::BGR24)
		{
			desc.InternalFormat = GL_RGB8;
			desc.Format = GL_BGR;
		}
		else if (asset.Format == ImageFormat::RGB24)
		{
			desc.InternalFormat = GL_RGB8;
			desc.Format = GL_RGB;
		}
		else if (asset.Format == ImageFormat::ARGB8888)
		{
			desc.InternalFormat = GL_BGRA;
			desc.Format = GL_BGRA;
		}
		else if (asset.Format == ImageFormat::INDEX8)
		{
			desc.InternalFormat = GL_R8;
			desc.Format = GL_RED;
		}
		else if (asset.Format == ImageFormat::ABGR8888)
		{
			desc.InternalFormat = GL_RGBA8;
			desc.Format = GL_RGBA;
			//desc.Type = GL_UNSIGNED_INT_8_8_8_8_REV;
		}
		else
		{
			std::cerr << "未知纹理格式" << std::endl;
			__debugbreak();
		}

		//return nullptr;
		auto tex = CreateTextureFromMemory(desc);

		return CreateRef<Texture2D>(tex);

	}

	VGObjectPtr TextureResourceManager::StaticLoadObject(const String& path)
	{
		// 检查文件是否过期，如果没有过期则查找缓存的纹理
		if (GetAssetManager()->IsExpiredAsset(path) == false)
		{
			if (m_CachedTextures.contains(path))
				return m_CachedTextures[path];
		}

		// 加载纹理资源
		Ref<TextureAsset> asset = GetAssetManager()->LoadAsset<TextureAsset>(path);

		if (asset == nullptr)
			return nullptr;

		// 创建渲染纹理
		auto texture = CreateRenderTexture(*asset.get());
		texture->SetResourcePath(path);

		// 缓存纹理
		m_CachedTextures[path] = texture;

		return texture;
	}

	VideoResourceManager::VideoResourceManager()
	{
		RegisterObjectLoader(typeid(VideoClip), this);
	}

	void VideoResourceManager::CreateManager()
	{
		if (GetInstanceValid() == true)
			return;

		new VideoResourceManager();
	}

	VGObjectPtr VideoResourceManager::StaticLoadObject(const String& path)
	{
		Ref<VideoAsset> asset = GetAssetManager()->LoadAsset<VideoAsset>(path, false);
		
		if (asset == nullptr)
			return nullptr;

		asset->videoClip->SetResourcePath(path);

		return asset->videoClip;
	}

	AudioResourceManager::AudioResourceManager()
	{
		RegisterObjectLoader(typeid(AudioClip), this);
	}

	void AudioResourceManager::CreateManager()
	{
		if (GetInstanceValid() == true)
			return;

		new AudioResourceManager();
	}

	VGObjectPtr AudioResourceManager::StaticLoadObject(const String& path)
	{
		Ref<AudioAsset> asset = GetAssetManager()->LoadAsset<AudioAsset>(path, false);

		if (asset == nullptr)
			return nullptr;

		asset->audioClip->SetResourcePath(path);

		return asset->audioClip;
	}

	void CreateResourceManagers()
	{
		TextureResourceManager::CreateManager();
		VideoResourceManager::CreateManager();
		AudioResourceManager::CreateManager();
	}
}
