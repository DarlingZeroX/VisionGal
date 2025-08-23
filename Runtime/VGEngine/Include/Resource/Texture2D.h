#pragma once
#include "../EngineConfig.h"
#include "../Core/Core.h"
#include "../Graphics/Interface/Texture.h"

namespace VisionGal {

	//struct RenderResource : public VGObject
	//{
	//	~RenderResource() override = default;
	//
	//	const String& GetResourcePath() { return m_ResourcePath; }
	//	void SetResourcePath(const String& path) { m_ResourcePath = path; }
	//
	//private:
	//	String m_ResourcePath;
	//};

	struct VG_ENGINE_API Texture2D : public VGEngineResource
	{
		Texture2D();
		Texture2D(Ref<VGFX::ITexture> texture);

		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D(Texture2D&&) noexcept = default;
		Texture2D& operator=(Texture2D&&) noexcept = default;

		~Texture2D() override = default;

		int Width();
		int Height();
		float2 Size();
		const VGFX::TextureDesc* GetTextureDesc();

		Ref<VGFX::ITexture>& GetTexture();
		void SetTexture(const Ref<VGFX::ITexture>& texture);

	private:
		Ref<VGFX::ITexture> m_Texture;
	};
}
