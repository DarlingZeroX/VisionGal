#include "Graphics/OpenGL/TextureBase.h"
#include "Graphics/OpenGL/ThrowMarco.h"

VISIONGAL_OPENGL_NAMESPACE_BEGIN

	TextureBase::TextureBase()
		:
		m_Slot(0), m_RendererID(0)
	{
	}

	TextureBase::TextureBase(int slot)
		:
		m_Slot(slot), m_RendererID(0)
	{
	}

	TextureBase::~TextureBase()
	{
		Delete();
	}

	TextureBase::TextureBase(TextureBase&& other) noexcept
	{
		*this = std::move(other);
	}

	TextureBase& TextureBase::operator=(TextureBase&& other) noexcept
	{
		m_RendererID = other.m_RendererID;
		m_Slot = other.m_Slot;

		other.m_RendererID = 0;
		other.m_Slot = 0;

		return *this;
	}

	void TextureBase::Bind() const
	{
		H_ASSERT_NOT_NULL(m_RendererID);

		ActiveTex();
		BindTex();
	}

	void TextureBase::Bind(uint32_t slot) const
	{
		H_ASSERT_NOT_NULL(m_RendererID);

		ActiveTex(slot);
		BindTex();
	}

	void TextureBase::Unbind() const
	{
		UnBindTex();
	}

	void TextureBase::Delete()
	{
		if (m_RendererID != NULL)
		{
			GL_THROW_INFO(glDeleteTextures(1, &m_RendererID));
			m_RendererID = NULL;
		}
	}

	unsigned int TextureBase::GetRendererID() const noexcept
	{
		return m_RendererID;
	}

	unsigned int TextureBase::GetSlot() const noexcept
	{
		return m_Slot;
	}

	void TextureBase::SetSlot(unsigned int slot) noexcept
	{
		m_Slot = slot;
	}

	bool TextureBase::operator==(const TextureBase& other) const
	{
		return m_RendererID == ((TextureBase&)other).m_RendererID;
	}

	void TextureBase::GenTex()
	{
		H_ASSERT_NULL(m_RendererID);

		GL_THROW_INFO(glGenTextures(1, &m_RendererID));
	}

	void TextureBase::BindTex() const
	{
		H_ASSERT_NOT_NULL(m_RendererID);

		GL_THROW_INFO(glBindTexture(GetTexType(), m_RendererID));
	}

	void TextureBase::UnBindTex() const
	{
		GL_THROW_INFO(glBindTexture(GetTexType(), 0));
	}

	void TextureBase::ActiveTex() const
	{
		GL_THROW_INFO(glActiveTexture(GL_TEXTURE0 + m_Slot));
	}

	void TextureBase::ActiveTex(int slot) const
	{
		GL_THROW_INFO(glActiveTexture(GL_TEXTURE0 + slot));
	}

	void TextureBase::TexFlitering(unsigned int flitering)
	{
		GL_THROW_INFO(glTexParameteri(GetTexType(), GL_TEXTURE_MIN_FILTER, (GLuint)flitering));
		GL_THROW_INFO(glTexParameteri(GetTexType(), GL_TEXTURE_MAG_FILTER, (GLuint)flitering));
	}

	void TextureBase::TexFlitering(unsigned int min, unsigned int mag)
	{
		GL_THROW_INFO(glTexParameteri(GetTexType(), GL_TEXTURE_MIN_FILTER, (GLuint)min));
		GL_THROW_INFO(glTexParameteri(GetTexType(), GL_TEXTURE_MAG_FILTER, (GLuint)mag));
	}

	void TextureBase::TexWrapping(GLuint wrapping)
	{
		GL_THROW_INFO(glTexParameteri(GetTexType(), GL_TEXTURE_WRAP_S, (GLuint)wrapping));
		GL_THROW_INFO(glTexParameteri(GetTexType(), GL_TEXTURE_WRAP_T, (GLuint)wrapping));
	}

	void TextureBase::TexBorderColor(const float4& color) const
	{
		GL_THROW_INFO(glTexParameterfv(GetTexType(), GL_TEXTURE_BORDER_COLOR, &color[0]));
	}

VISIONGAL_OPENGL_NAMESPACE_END


