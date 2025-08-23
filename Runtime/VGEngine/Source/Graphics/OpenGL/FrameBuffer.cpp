#include "Graphics/OpenGL/FrameBuffer.h"
#include "Graphics/OpenGL/ThrowMarco.h"

VISIONGAL_OPENGL_NAMESPACE_BEGIN

	FrameBuffer::FrameBuffer()
		:
		m_RendererID(0)
	{
		CreateImp();
	}

	FrameBuffer::~FrameBuffer()
	{
		Delete();
	}

	Ref<FrameBuffer> FrameBuffer::Create()
	{
		Ref<FrameBuffer> fb = CreateRef<FrameBuffer>();

		return fb;
	}

	void FrameBuffer::Gen()
	{
		GL_THROW_INFO(glGenFramebuffers(1, &m_RendererID));
	}

	void FrameBuffer::Bind() const
	{
		GL_THROW_INFO(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	}

	void FrameBuffer::Unbind() const
	{
		GL_THROW_INFO(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::Delete()
	{
		GL_THROW_INFO(glDeleteFramebuffers(1, &m_RendererID));
	}

	bool FrameBuffer::CheckStatus()
	{
		return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	}

	void FrameBuffer::DrawBuffers(unsigned int size)
	{
		// - ����OpenGL���ǽ�Ҫʹ��(֡�����)������ɫ������������Ⱦ
		std::vector<GLuint> attachments;
		attachments.resize(size);

		for (unsigned int i = 0; i < size; ++i)
		{
			attachments[i] = GL_COLOR_ATTACHMENT0 + size;
		}

		GL_THROW_INFO(glDrawBuffers(size, attachments.data()));
	}

	void FrameBuffer::CreateImp()
	{
		Gen();
		Bind();
	}

	void FrameBufferTexture::CreateFBTInline(unsigned int width, unsigned int height, Type type, unsigned int slot)
	{
		m_Desc.Width = width;
		m_Desc.Height = height;

		m_Type = type;
		SetSlot(slot);
		m_FrameBufferSlot = slot;

		GenTex();
		Bind();

		m_FrameBufferBindType = GL_COLOR_ATTACHMENT0 + m_FrameBufferSlot;

		//Generate buffer
		switch (type)
		{
		case Type::COLOR:
			GL_THROW_INFO(glTexImage2D(
				GL_TEXTURE_2D, 0,
				GL_RGBA,
				width, height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE,
				NULL));
			break;
		case Type::NORMAL:
			GL_THROW_INFO(glTexImage2D(
				GL_TEXTURE_2D, 0,
				GL_RGB16F,
				width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE,
				NULL));
			break;
		case Type::ALBEDO_SPEC:
			GL_THROW_INFO(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL));
			break;
		case Type::DEPTH24_STENCIL8:
			GL_THROW_INFO(glTexImage2D(
				GL_TEXTURE_2D, 0,
				GL_DEPTH24_STENCIL8,
				width, height, 0,
				GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8,
				NULL
			));
			m_FrameBufferBindType = GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		case Type::DEPTH_COMPONENT:
			GL_THROW_INFO(glTexImage2D(
				GL_TEXTURE_2D, 0,
				GL_DEPTH_COMPONENT,
				width, height, 0,
				GL_DEPTH_COMPONENT, GL_FLOAT,
				NULL
			));
			m_FrameBufferBindType = GL_DEPTH_ATTACHMENT;
			break;
		default:
			throw "Attachment type not exist";
			break;
		}

		//Set texture paramerter
		switch (type)
		{
		case Type::DEPTH24_STENCIL8:
		case Type::DEPTH_COMPONENT:
			//��Ⱥ�ģ�建������ڽ�ȡֵ
			TexFlitering(GL_NEAREST);
			//������Ȼ��峬�������Ĭ�����
			TexWrapping(GL_CLAMP_TO_BORDER);
			break;
		default:
			TexFlitering(GL_LINEAR);
			break;
		}

		Unbind();
	}

	Ref<FrameBufferTexture> FrameBufferTexture::Create(unsigned int width, unsigned int height, Type type, unsigned int slot)
	{
		Ref<FrameBufferTexture> fbt = CreateRef<FrameBufferTexture>();
		fbt->CreateFBTInline(width, height, type, slot);

		return fbt;
	}

	void FrameBufferTexture::AttachToFrameBuffer()
	{
		/// <summary>
		/// glFramebufferTexture2D(target,attachment,textarget,texture,level)
		/// target��������������֡�������͵�Ŀ�꣨���ơ���ȡ�����߶��У���
		/// attachment�����������ӵĸ��������͡��������Ǹ��ӵ���һ����ɫ��������Ҫע�⣬�����Ǹ�0�ǰ�ʾ���ǿ��Ը���1��������ɫ�ĸ��������ǻ��ں���Ľ̳���̸����
		///	textarget����ϣ�����ӵ��������͡�
		///	texture�����ӵ�ʵ������
		///	level��Mipmap level����������Ϊ0��
		/// </summary>

		GL_THROW_INFO(glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			m_FrameBufferBindType,
			GL_TEXTURE_2D,
			GetRendererID(),
			0
		));
	}

	int FrameBufferTexture::Width()
	{
		return GetDesc().Width;
	}

	int FrameBufferTexture::Height()
	{
		return GetDesc().Height;
	}


	/// <summary>
	/// RenderBuffer Object Attachment
	/// </summary>
	FrameBufferDepth::FrameBufferDepth()
	{
		m_RenderBufferID = 0;
		m_Type = Type::DEPTH24_STENCIL8;
		m_AttachType = 0;
		m_StorageType = 0;
	}

	FrameBufferDepth::~FrameBufferDepth()
	{
		Delete();
	}

	Ref<FrameBufferDepth> FrameBufferDepth::Create(unsigned int width, unsigned int height, Type type)
	{
		Ref<FrameBufferDepth> fbt = CreateRef<FrameBufferDepth>();
		fbt->CreateImp(width, height, type);

		return fbt;
	}

	bool FrameBufferDepth::CreateImp(
		unsigned int width,
		unsigned int height,
		Type type
	)
	{
		m_Type = type;
		Gen();
		Bind();

		switch (type)
		{
		case Type::DEPTH24_STENCIL8:
			m_AttachType = GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		case Type::DEPTH_COMPONENT:
			m_AttachType = GL_DEPTH_ATTACHMENT;
			break;
		default:
			Unbind();
			return false;
		}
		m_StorageType = (GLenum)type;
		SetStorage(width, height);

		Unbind();

		return true;
	}

	void FrameBufferDepth::AttachToFrameBuffer() const
	{
		GL_THROW_INFO(glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			m_AttachType,
			GL_RENDERBUFFER,
			m_RenderBufferID
		));
	}

	void FrameBufferDepth::Bind() const
	{
		GL_THROW_INFO(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID));
	}

	void FrameBufferDepth::Unbind() const
	{
		GL_THROW_INFO(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	}

	void FrameBufferDepth::Delete()
	{
		if (m_RenderBufferID != 0)
		{
			GL_THROW_INFO(glDeleteRenderbuffers(1, &m_RenderBufferID));
			m_RenderBufferID = 0;
		}
	}

	void FrameBufferDepth::SetStorage(int width, int height)
	{
		GL_THROW_INFO(glRenderbufferStorage(GL_RENDERBUFFER, m_StorageType, width, height));
	}

	unsigned int FrameBufferDepth::GetRendererID() const
	{
		return m_RenderBufferID;
	}

	GLenum FrameBufferDepth::GetAttachType() const
	{
		return m_AttachType;
	}

	GLenum FrameBufferDepth::GetStorageType() const
	{
		return m_StorageType;
	}

	void FrameBufferDepth::Gen()
	{
		GL_THROW_INFO(glGenRenderbuffers(1, &m_RenderBufferID));
	}

VISIONGAL_OPENGL_NAMESPACE_END

