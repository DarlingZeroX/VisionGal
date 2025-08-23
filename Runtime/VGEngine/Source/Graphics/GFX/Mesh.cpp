#include "Graphics/GFX/Mesh.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

VertexBuffer::~VertexBuffer()
{
	Delete();
}

void VertexBuffer::Bind() const
{
	bgfx::setVertexBuffer(0, m_Handle);
}

void VertexBuffer::Delete()
{
	bgfx::destroy(GetHandle());
}

void VertexBuffer::Create(const void* vertices, unsigned int size, const bgfx::VertexLayout& layout)
{
	m_Handle = bgfx::createVertexBuffer(
		bgfx::makeRef(vertices, size),
		layout
	);
}

//////////////////////////////////////////////////////////////////////////////////////////
/// IndexBuffer
//////////////////////////////////////////////////////////////////////////////////////////
IndexBuffer::~IndexBuffer()
{
	Delete();
}

void IndexBuffer::Create(const void* indices, unsigned int stride, unsigned int count)
{
	m_Count = count;

	m_Handle = bgfx::createIndexBuffer(bgfx::makeRef(indices, stride * count), BGFX_BUFFER_INDEX32);
}

void IndexBuffer::Bind() const
{
	bgfx::setIndexBuffer(m_Handle);
}

void IndexBuffer::Delete()
{
	bgfx::destroy(GetHandle());
}

//////////////////////////////////////////////////////////////////////////////////////////
/// StaticMesh
//////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::Bind() const
{
	m_Vertices->Bind();
	m_Indices->Bind();
}

VISIONGAL_GFX_NAMESPACE_END