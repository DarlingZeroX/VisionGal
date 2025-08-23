#include "Interface.h"

VISIONGAL_GFX_NAMESPACE_BEGIN

	class VertexBuffer :public Bindable
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&) = delete;
		~VertexBuffer();

		template<class V>
		VertexBuffer(std::vector<V>& vertices, const bgfx::VertexLayout& layout)
		{
			Create(vertices, layout);
		}

		template<class V>
		VertexBuffer(V* vertices, unsigned int count, const bgfx::VertexLayout& layout)
		{
			Create(vertices, count, layout);
		}

	public:
		virtual void Bind() const override;
		void Delete();
		const bgfx::VertexBufferHandle& GetHandle() const noexcept { return m_Handle; }
	private:
		template<class V>
		void Create(std::vector<V>& vertices, const bgfx::VertexLayout& layout)
		{
			Create(vertices.data(), vertices.size(), layout);
		}

		template<class V>
		void Create(const V* vertices, unsigned int count, const bgfx::VertexLayout& layout)
		{
			m_Stride = sizeof(V);
			m_Size = count * m_Stride;

			Create(vertices, m_Size, layout);
		}

		void Create(const void* vertices, unsigned int size, const bgfx::VertexLayout& layout);
	private:
		unsigned int m_Stride;
		unsigned int m_Size;

		bgfx::VertexBufferHandle m_Handle;
	};


	class IndexBuffer :public Bindable
	{
	public:
		IndexBuffer() = default;
		~IndexBuffer();

		template<class V>
		IndexBuffer(std::vector<V>& indices)
		{
			Create(indices);
		}

		template<class V>
		IndexBuffer(const V* indices, unsigned int count)
		{
			Create(indices, count);
		}
	public:
		virtual void Bind() const override;
		void Delete();
		unsigned int GetCount() noexcept { return m_Count; }
		const bgfx::IndexBufferHandle& GetHandle() const noexcept { return m_Handle; }
	protected:
		template<class V>
		void Create(const V* indices, unsigned int count)
		{
			unsigned int stride = sizeof(V);

			Create(indices, stride, count);
		}

		void Create(const void* indices, unsigned int stride, unsigned int count);

		template<class V>
		void Create(std::vector<V>& indices)
		{
			Create(indices.data(), indices.size());
		}
	protected:
		unsigned int m_Count;
		bgfx::IndexBufferHandle m_Handle;
	};

	class StaticMesh
	{
	public:
		//StaticMesh() = default;
		StaticMesh(StaticMesh& mesh) = delete;
		StaticMesh& operator=(StaticMesh& mesh) = delete;
		virtual ~StaticMesh() = default;

		template<class VERTEX, class INDEX>
		StaticMesh(
			std::vector<VERTEX>& vertices,
			std::vector<INDEX>& indices,
			const bgfx::VertexLayout& elements
		)
		{
			m_Vertices = std::make_unique<VertexBuffer>(vertices, elements);
			m_Indices = std::make_unique<IndexBuffer>(indices);
		}

		VertexBuffer* GetVertexBuffer() { return m_Vertices.get(); }
		IndexBuffer* GetIndexBuffer() { return m_Indices.get(); }
	
		void Bind() const;	
	private:
		std::unique_ptr<VertexBuffer> m_Vertices;
		std::unique_ptr<IndexBuffer> m_Indices;
	};

VISIONGAL_GFX_NAMESPACE_END