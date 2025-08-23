#pragma once

#include "Interface.h"

VISIONGAL_OPENGL_NAMESPACE_BEGIN

	class TextureBase :public Bindable, public Renderable
	{
	public:
		TextureBase();
		TextureBase(int slot);
		TextureBase(TextureBase&) = delete;
		TextureBase& operator=(TextureBase&) = delete;
		~TextureBase() override;
		TextureBase(TextureBase&& other) noexcept;
		TextureBase& operator=(TextureBase&& other) noexcept;
		virtual GLenum GetTexType() const noexcept = 0;
	public:
		virtual void Bind() const override;
		virtual void Bind(uint32_t slot) const;
		virtual void Unbind() const override;
		virtual void Delete();

		virtual unsigned int GetRendererID() const noexcept;
		virtual unsigned int GetSlot() const noexcept;
		virtual void SetSlot(unsigned int slot) noexcept;

		virtual bool operator==(const TextureBase& other) const;
	protected:
		virtual void GenTex();
		virtual void BindTex() const;
		virtual void UnBindTex() const;
		virtual void ActiveTex() const;
		virtual void ActiveTex(int slot) const;
		virtual void TexFlitering(unsigned int flitering);
		virtual void TexFlitering(unsigned int min, unsigned int mag);
		virtual void TexWrapping(GLuint wrapping);			/// 纹理环绕方式

		/// CLAMP_TO_BORDER 环绕方式时，纹理超过边界时的颜色
		virtual void TexBorderColor(const float4& color) const;
	private:
		unsigned int m_RendererID = 0;
		unsigned int  m_Slot = 0;
	};

VISIONGAL_OPENGL_NAMESPACE_END