#pragma once
#include "../Interface/Texture.h"
#include "Interface.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

class Texture2D : public ITexture
{
public:
	Texture2D() = default;
	Texture2D(Texture2D&) = delete;
	~Texture2D() override = default;

	int Width() const noexcept { return m_Desc.Width; }
	int Height() const noexcept { return m_Desc.Height; }

	static Ref<Texture2D> CreateFromMemory(const TextureDesc& desc);

	const TextureDesc& GetTextureDesc() override;
	void* GetShaderResourceView() override;

	const bgfx::TextureHandle& GetHandle() const noexcept { return m_Handle; }
protected:
	bool CreateFromMemoryImp(const TextureDesc& desc);
protected:
	TextureDesc m_Desc;
	bgfx::TextureHandle m_Handle;
};

VISIONGAL_GFX_NAMESPACE_END