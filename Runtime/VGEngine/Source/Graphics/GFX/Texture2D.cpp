#include "Graphics/GFX/Texture2D.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

bool Texture2D::CreateFromMemoryImp(const TextureDesc& desc)
{
	m_Desc = desc;
	uint16_t width = desc.Width;
	uint16_t height = desc.Height;
	bgfx::TextureFormat::Enum format = static_cast<bgfx::TextureFormat::Enum>( desc.Format );

	bgfx::TextureHandle texture = bgfx::createTexture2D(
		width, height,         // 纹理宽度和高度
		false,              // 是否生成多级渐远纹理
		1,                  // 纹理层数
		format,  // 纹理格式
		BGFX_TEXTURE_NONE,  // 纹理标志
		bgfx::makeRef(desc.Data,desc.DataSize)   // 纹理数据（实际项目中需提供图片数据）
	);

	return true;
}

Ref<Texture2D> Texture2D::CreateFromMemory(const TextureDesc& desc)
{
	auto Tex = std::make_shared<Texture2D>();

	Tex->CreateFromMemoryImp(desc);

	return Tex;
}

const TextureDesc& Texture2D::GetTextureDesc()
{
	return m_Desc;
}

void* Texture2D::GetShaderResourceView()
{
	return reinterpret_cast<void*>(&m_Handle);;
}

VISIONGAL_GFX_NAMESPACE_END

