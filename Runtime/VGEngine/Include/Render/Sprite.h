#pragma once
#include "../Resource/Texture2D.h"
#include "../Core/Core.h"
#include "../EngineConfig.h"
#include "../Interface/RenderInterface.h"
#include "../Graphics/Interface/VGFX.h"

namespace VisionGal {

	class VG_ENGINE_API FullScreenQuad : public VGObject
	{
	public:
		FullScreenQuad();
		FullScreenQuad(const FullScreenQuad&) = delete;
		FullScreenQuad& operator=(const FullScreenQuad&) = delete;
		FullScreenQuad(FullScreenQuad&&) noexcept = default;
		FullScreenQuad& operator=(FullScreenQuad&&) noexcept = default;
		~FullScreenQuad() override = default;

		static Ref<FullScreenQuad> Create();
		static VGFX::IStaticMesh* GetFullScreenQuadMesh();

		VGFX::IStaticMesh* GetMesh();
		VGFX::ITexture* GetTexture();
		void SetTexture(const Ref<VGFX::ITexture>& tex);
	private:
		static Ref<VGFX::IStaticMesh> s_Mesh;
		Ref<Texture2D> m_Texture;
	};

	class VG_ENGINE_API Sprite : public ISprite
	{
	public:
		Sprite(Ref<Texture2D> tex, float2 size, float2 pos = float2(0.f));
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		Sprite(Sprite&&) noexcept = default;
		Sprite& operator=(Sprite&&) noexcept = default;
		~Sprite() override = default;

		static Ref<Sprite> Create(Ref<Texture2D> tex, float2 size);

		VGFX::IStaticMesh* GetMesh() override;
		VGFX::ITexture* GetITexture() override;
		float2 GetSize() const;
		float2 GetPosition() const;
		Texture2D* GetTexture2D() const;
	protected:
		void CreateMesh(float2 size, float2 pos);
	private:
		Ref<VGFX::IStaticMesh> m_Mesh;
		Ref<Texture2D> m_Texture;
		float2 m_Size;
		float2 m_Position;
	};
}
