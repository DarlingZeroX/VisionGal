#include "Audio/AudioTransformScript.h"

namespace VisionGal
{
	AudioFadeInOutTransformScript::AudioFadeInOutTransformScript(Direction direction)
	{
		m_Script = CreateRef<AudioTransformScript>();

		switch (direction)
		{
		case Direction::In:
			m_StartVolume = 0.0f;
			m_EndVolume = 1.0f;
			break;
		case Direction::Out:
			m_StartVolume = 1.0f;
			m_EndVolume = 0.0f;
			break;
		}
	}

	void AudioFadeInOutTransformScript::SetDuration(float duration)
	{
		m_Duration = duration;
	}

	void AudioFadeInOutTransformScript::SetEasing(EasingFunction easing)
	{
		m_EasingFunction = easing;
	}

	void AudioFadeInOutTransformScript::Start()
	{
		m_Script->TransformVolume(
			Core::GetCurrentTime(),
			m_Duration,
			m_StartVolume,
			m_EndVolume,
			m_EasingFunction
		);
	}

	void AudioFadeInOutTransformScript::OnUpdate(Horizon::HEntityInterface* entity)
	{
		m_Script->OnUpdate(entity);
	}
}
