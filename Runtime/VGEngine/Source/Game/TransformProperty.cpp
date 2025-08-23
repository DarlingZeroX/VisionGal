#include "Game/TransformProperty.h"
#include <HCore/Include/Math/HMathHelper.h>

namespace VisionGal
{
	EasingFunction EasingCallbacks::linear = [](float t) { return t; };

	void TransformProperty::Update(float currentTime)
	{
		if (active == false)
		{
			return;
		}

		if (isFinish == true)
		{
			active = false;
			return;
		}

		if (currentTime < startTime)
			return;

		float elapsed = currentTime - startTime;
		if (elapsed >= duration) {
			currentValue = endValue;
			isFinish = true;
		}
		else {
			float t = elapsed / duration;
			currentValue = startValue + easing(t) * (endValue - startValue);
		}

		// ≈–∂œ «∑ÒΩ· ¯
		if (startValue < endValue)
		{
			if (currentValue >= endValue)
			{
				isFinish = true;
			}
		}
		else
		{
			if (currentValue <= endValue)
			{
				isFinish = true;
			}
		}
	}

	void TransformProperty::Start(float startTime, float duration, float startValue, float endValue,
		EasingFunction easing)
	{
		this->startTime = startTime;
		this->duration = duration;
		this->startValue = startValue;
		this->endValue = endValue;
		this->easing = easing;
		this->active = true;
		this->isFinish = false;
	}

	void TransformProperty::Finish()
	{
		currentValue = endValue;
	}

	bool TransformProperty::IsFinish()
	{
		return active;
	}
}
