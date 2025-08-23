#include "Galgame/SpriteTransformScript.h"
#include "Galgame/GameEngineCore.h"

namespace VisionGal::GalGame
{
	ScrollTransformScript::ScrollTransformScript(Direction direction, float2 texSize)
	{
		m_Script = CreateRef<SpriteTransformScript>();

		switch (direction)
		{
		case Direction::Left:
			m_StartOffset = -GameEngineCore::GetSpriteXOffset(texSize.x);
			m_EndOffset = -m_StartOffset;
			m_IsHorizontal = true;
			break;
		case Direction::Right:
			m_StartOffset = GameEngineCore::GetSpriteXOffset(texSize.x);
			m_EndOffset = -m_StartOffset;
			m_IsHorizontal = true;
			break;
		case Direction::Up:
			m_StartOffset = GameEngineCore::GetSpriteYOffset(texSize.y);
			m_EndOffset = -m_StartOffset;
			m_IsHorizontal = false;
			break;
		case Direction::Down:
			m_StartOffset = -GameEngineCore::GetSpriteYOffset(texSize.y);
			m_EndOffset = -m_StartOffset;
			m_IsHorizontal = false;
			break;
		}

	}

	void ScrollTransformScript::SetDuration(float duration)
	{
		m_Duration = duration;
	}

	void ScrollTransformScript::SetEasing(EasingFunction easing)
	{
		m_EasingFunction = easing;
	}

	void ScrollTransformScript::Start()
	{
		if (m_IsHorizontal)
		{
			m_Script->TransformXOffset(
				Core::GetCurrentTime(),
				m_Duration,
				m_StartOffset,
				m_EndOffset,
				m_EasingFunction
			);
		}
		else
		{
			m_Script->TransformYOffset(
				Core::GetCurrentTime(), 
				m_Duration,
				m_StartOffset,
				m_EndOffset, 
				m_EasingFunction
			);
		}
	}

	void ScrollTransformScript::OnUpdate(Horizon::HEntityInterface* entity)
	{
		m_Script->OnUpdate(entity);
	}

	FadeInOutTransformScript::FadeInOutTransformScript(Direction direction)
	{
		m_Script = CreateRef<SpriteTransformScript>();

		switch (direction)
		{
		case Direction::In:
			m_StartOffset = 0.0f;
			m_EndOffset = 1.0f;
			break;
		case Direction::Out:
			m_StartOffset = 1.0f;
			m_EndOffset = 0.0f;
			break;
		}
	}

	void FadeInOutTransformScript::SetDuration(float duration)
	{
		m_Duration = duration;
	}

	void FadeInOutTransformScript::SetEasing(EasingFunction easing)
	{
		m_EasingFunction = easing;
	}

	void FadeInOutTransformScript::Start()
	{
		m_Script->TransformAlpha(
			Core::GetCurrentTime(),
			m_Duration,
			m_StartOffset,
			m_EndOffset,
			m_EasingFunction
		);
	}

	void FadeInOutTransformScript::OnUpdate(Horizon::HEntityInterface* entity)
	{
		m_Script->OnUpdate(entity);
	}
}
