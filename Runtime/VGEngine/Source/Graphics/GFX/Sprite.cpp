#include "Graphics/GFX/Sprite.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

Sprite::Sprite()
{
	Initialize();
}

void Sprite::Initialize()
{
	m_Vertices = {
		// λ��          // �������꣨�޸ĺ�
		 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, // ����
		 1.0f, -1.0f, 0.0f,  1.0f, 1.0f, // ����
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f, // ����
		-1.0f,  1.0f, 0.0f,  0.0f, 0.0f  // ����
	};

	static std::vector<unsigned int> indices = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	static bgfx::VertexLayout ms_layout;
	ms_layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true)
		.end();


	m_Mesh = std::make_unique<StaticMesh>(m_Vertices, indices, ms_layout);
}

VISIONGAL_GFX_NAMESPACE_END


