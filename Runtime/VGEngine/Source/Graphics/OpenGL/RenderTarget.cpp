#include "Graphics/OpenGL/RenderTarget.h"
#include "Graphics/OpenGL/ThrowMarco.h"

VISIONGAL_OPENGL_NAMESPACE_BEGIN
	Ref<RenderTarget2D> RenderTarget2D::Create(unsigned int width, unsigned int height)
	{
		auto rt = CreateRef<RenderTarget2D>();
		rt->CreateImp(width, height);

		return rt;
	}

	void RenderTarget2D::CopyToTexture(VGFX::ITexture* texture)
	{
		m_FrameBuffer->Bind();

		Texture2D* glTexture = dynamic_cast<Texture2D*>(texture);
		glTexture->Bind();

		GL_THROW_INFO(glCopyTexSubImage2D(GL_TEXTURE_2D,  // Ŀ����������
			0,              // mipmap ����
			0, 0,           // Ŀ������ƫ��
			0, 0,           // Դ֡�����������½�
			m_ColorFBT->Width(), m_ColorFBT->Height())); // ��������ߴ�

		m_FrameBuffer->Unbind();
	}

	void RenderTarget2D::BindColorAttachments()
	{
		GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
		GL_THROW_INFO(glDrawBuffers(1, attachments));
	}

	bool RenderTarget2D::CreateImp(unsigned int width, unsigned int height)
	{
		m_FrameBuffer = CreateRef<FrameBuffer>();
		m_FrameBuffer->Bind();

		m_ColorFBT = FrameBufferTexture::Create(width, height, FrameBufferTexture::Type::COLOR);
		m_ColorFBT->AttachToFrameBuffer();

		BindColorAttachments();

		m_DepthFBT = FrameBufferDepth::Create(width, height);
		m_DepthFBT->AttachToFrameBuffer();

		if (m_FrameBuffer->CheckStatus() == false)
		{
			m_FrameBuffer->Unbind();
			return false;
		}

		m_FrameBuffer->Unbind();
		return true;
	}



VISIONGAL_OPENGL_NAMESPACE_END