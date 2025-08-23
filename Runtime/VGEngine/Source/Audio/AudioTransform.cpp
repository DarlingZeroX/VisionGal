#include "Audio/AudioTransform.h"

#include "Scene/Components.h"

namespace VisionGal
{
	AudioTransformState::AudioTransformState()
	{
		Reset();
	}

	void AudioTransformState::SetAll(const TransformData& data)
	{
		volume.currentValue = data.volume;
		visible.currentValue = data.visible ? 1.0f : 0.0f;
	}

	void AudioTransformState::SetAll(const AudioTransformState& data)
	{
		volume.currentValue = data.volume.currentValue;
		visible.currentValue = data.visible.currentValue;
	}

	AudioTransformState::TransformData AudioTransformState::GetCurrent() const
	{
		TransformData data;
		data.volume = volume.currentValue;
		data.visible = visible.currentValue > 0.5f;
		return data;
	}

	void AudioTransformState::Finish()
	{
		TravelProperty([this](TransformProperty& property)
			{
				property.Finish();
			});
	}

	bool AudioTransformState::IsFinish()
	{
		return volume.IsFinish() &&
			visible.IsFinish();
	}

	void AudioTransformState::Reset()
	{
		SetAll(TransformData());
		TravelProperty([this](TransformProperty& property)
			{
				property.active = false;
				property.easing = EasingCallbacks::linear;
			});
	}

	void AudioTransformState::TravelProperty(std::function<void(TransformProperty& property)> callback)
	{
		callback(volume);
		callback(visible);
	}

	void AudioTransformScript::TransformVolume(float startTime, float duration, float startVal, float endVal,
		EasingFunction easing)
	{
		state.volume.Start(startTime, duration, startVal, endVal, easing);
	}

	void AudioTransformScript::TransformVisible(float startTime, float duration, bool startVal, float endVal,
		EasingFunction easing)
	{
		state.visible.Start(startTime, duration, startVal ? 1.0f : 0.0f, endVal ? 1.0f : 0.0f, easing);
	}

	void AudioTransformScript::Reset()
	{
		state.Reset();
	}

	void AudioTransformScript::Finish()
	{
		state.Finish();
	}

	void AudioTransformScript::OnUpdate(Horizon::HEntityInterface* entity)
	{
		float currentTime = GetCurrentTime(); // 假设存在获取当前时间的函数

		// 更新所有属性
		state.TravelProperty([this, currentTime](TransformProperty& property)
			{
				property.Update(currentTime);
			});

		ApplyStateToEntity(entity);
	}

	void AudioTransformScript::OnFixUpdate(Horizon::HEntityInterface* entity)
	{

	}

	float AudioTransformScript::GetCurrentTime() const
	{
		return Core::GetCurrentTime();
	}

	void AudioTransformScript::ApplyStateToEntity(Horizon::HEntityInterface* entity)
	{
		auto* audioSource = entity->GetComponent<AudioSourceComponent>();
		if (audioSource)
		{
			if (state.volume.active)
			{
				audioSource->SetVolume(state.volume.currentValue);
				//H_LOG_INFO("state.volume.currentValue %f", state.volume.currentValue);
			}
		}
	}
}
