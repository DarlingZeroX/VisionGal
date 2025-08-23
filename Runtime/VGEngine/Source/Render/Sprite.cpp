#include "Render/Sprite.h"
#include "Graphics/OpenGL/Core.h"

namespace VisionGal
{
	Ref<VGFX::IStaticMesh> FullScreenQuad::s_Mesh = nullptr;

	FullScreenQuad::FullScreenQuad()
	{
		m_Texture = CreateRef<Texture2D>();
		GetFullScreenQuadMesh();
	}

	Ref<FullScreenQuad> FullScreenQuad::Create()
	{
		return CreateRef<FullScreenQuad>();
	}

	VGFX::IStaticMesh* FullScreenQuad::GetFullScreenQuadMesh()
	{
		if (s_Mesh == nullptr)
		{
			static std::vector<float> vertices = {
				// λ��          // �������꣨�޸ĺ�
				 1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // ����
				 1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // ����
				-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // ����
				-1.0f,  1.0f, 0.0f,  0.0f, 1.0f  // ����
			};
			static std::vector<unsigned int> indices = {  // note that we start from 0!
				0, 1, 3,  // first Triangle
				1, 2, 3   // second Triangle
			};

			static const std::vector<VGFX::VertexElement::IElement*> elements =
			{
				&VGFX::VertexElement::Position3,
				&VGFX::VertexElement::Texture2D
			};

			s_Mesh = VGFX::CreateStaticMesh(vertices, indices, elements);

			//m_Mesh = std::make_unique<StaticMesh>(m_Vertices, indices, elements);
		}

		return s_Mesh.get();
	}

	VGFX::IStaticMesh* FullScreenQuad::GetMesh()
	{
		if (s_Mesh != nullptr)
			return s_Mesh.get();
		return nullptr;
	}

	VGFX::ITexture* FullScreenQuad::GetTexture()
	{
		if (m_Texture != nullptr && m_Texture->GetTexture() != nullptr)
			return m_Texture->GetTexture().get();
		return nullptr;
	}

	void FullScreenQuad::SetTexture(const Ref<VGFX::ITexture>& tex)
	{
		m_Texture->SetTexture(tex);
	}

	Sprite::Sprite(Ref<Texture2D> tex, float2 size, float2 pos)
		:m_Texture(tex)
	{
		CreateMesh(size, pos);
	}

	Ref<Sprite> Sprite::Create(Ref<Texture2D> tex, float2 size)
	{
		return CreateRef<Sprite>(tex, size);
	}

	VGFX::IStaticMesh* Sprite::GetMesh()
	{
		if (m_Mesh != nullptr)
			return m_Mesh.get();
		return nullptr;
	}

	VGFX::ITexture* Sprite::GetITexture()
	{
		if (m_Texture != nullptr && m_Texture->GetTexture() != nullptr)
			return m_Texture->GetTexture().get();
		return nullptr;
	}

	float2 Sprite::GetSize() const
	{
		return m_Size;
	}

	float2 Sprite::GetPosition() const
	{
		return m_Position;
	}

	Texture2D* Sprite::GetTexture2D() const
	{
		if (m_Texture != nullptr)
			return m_Texture.get();
		return nullptr;
	}

	void Sprite::CreateMesh(float2 size, float2 pos)
	{
		m_Size = size;
		m_Position = pos;

		float width = size.x;
		float height = size.y;  // �����ߣ��߼���λ��
		float posX = pos.x;
		float posY = pos.y;  // ��������λ��

		std::vector<float> vertices = {
			// λ��(x,y,z)           // ��������(u,v)
			posX - width / 2, posY - height / 2, 0.0f,    0.0f, 1.0f,  // ����
			posX + width / 2, posY - height / 2, 0.0f,    1.0f, 1.0f,  // ����
			posX - width / 2, posY + height / 2, 0.0f,    0.0f, 0.0f,  // ����
			posX + width / 2, posY + height / 2, 0.0f,    1.0f, 0.0f   // ����
		};

		static std::vector<unsigned int> indices = {  // note that we start from 0!
			0, 1, 2,  // ��һ��������
			1, 3, 2   // �ڶ���������
		};

		static const std::vector<VGFX::VertexElement::IElement*> elements =
		{
			&VGFX::VertexElement::Position3,
			&VGFX::VertexElement::Texture2D
		};

		m_Mesh = VGFX::CreateStaticMesh(vertices, indices, elements);
	}
}
