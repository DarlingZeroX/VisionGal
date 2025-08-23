#include "Graphics/GFX/Texture2D.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

bool Texture2D::CreateFromMemoryImp(const TextureDesc& desc)
{
	m_Desc = desc;
	uint16_t width = desc.Width;
	uint16_t height = desc.Height;
	bgfx::TextureFormat::Enum format = static_cast<bgfx::TextureFormat::Enum>( desc.Format );

	bgfx::TextureHandle texture = bgfx::createTexture2D(
		width, height,         // �����Ⱥ͸߶�
		false,              // �Ƿ����ɶ༶��Զ����
		1,                  // �������
		format,  // �����ʽ
		BGFX_TEXTURE_NONE,  // �����־
		bgfx::makeRef(desc.Data,desc.DataSize)   // �������ݣ�ʵ����Ŀ�����ṩͼƬ���ݣ�
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

