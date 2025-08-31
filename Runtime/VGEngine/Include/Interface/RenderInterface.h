#pragma once
//#include "../Graphics/OpenGL/Sprite.h"
#include "../Resource/Texture2D.h"
#include "../Core/Core.h"
#include "../Graphics/Interface/Mesh.h"

namespace VisionGal
{
	enum class RenderPipelineIndex: uint
	{
		CoreRenderPipeline = 0,
		ScreenPipeline = 1,
		GalGamePipeline = 2,
	};

	struct ISprite
	{
		virtual ~ISprite() = default;

		virtual VGFX::IStaticMesh* GetMesh() = 0;
		virtual VGFX::ITexture* GetITexture() = 0;
	};

	struct ISpriteEffect
	{
		virtual ~ISpriteEffect() = default;

		virtual void ApplyEffect(ISprite* sprite) = 0;
	};

	struct ISceneTransition
	{
		virtual ~ISceneTransition() = default;

		virtual void SetPrevFrame(VGFX::ITexture* texture) = 0;
		virtual void SetNextFrame(VGFX::ITexture* texture) = 0;

		virtual const String& GetLayer() = 0;
		virtual void SetLayer(const String& layer) = 0;
		virtual void Transition() = 0;
		virtual void SetDuration(float duration) = 0;
		virtual void Start() = 0;
		virtual void Finish() = 0;
		virtual bool IsFinish() = 0;
		virtual float GetProgress() const noexcept = 0;
	};
}