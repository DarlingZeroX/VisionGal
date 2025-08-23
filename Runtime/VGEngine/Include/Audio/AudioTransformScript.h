#pragma once
#include "AudioTransform.h"

namespace VisionGal
{
    class AudioFadeInOutTransformScript : public ITransformScript
    {
    public:
        enum class Direction
        {
            In,
            Out
        };

        AudioFadeInOutTransformScript(Direction direction);
        ~AudioFadeInOutTransformScript() override = default;
        AudioFadeInOutTransformScript(const AudioFadeInOutTransformScript&) = delete;
        AudioFadeInOutTransformScript& operator=(const AudioFadeInOutTransformScript&) = delete;
        AudioFadeInOutTransformScript(AudioFadeInOutTransformScript&&) noexcept = default;
        AudioFadeInOutTransformScript& operator=(AudioFadeInOutTransformScript&&) noexcept = default;

        void SetDuration(float duration);
        void SetEasing(EasingFunction easing);
		void SetInVolume(float volume) { m_EndVolume = volume; }
		void SetOutVolume(float volume) { m_StartVolume = volume; }
        void Start() override;

        void OnUpdate(Horizon::HEntityInterface* entity) override;
    private:
        Ref<AudioTransformScript> m_Script;

        Direction m_Direction = Direction::In;
        float m_StartVolume, m_EndVolume;
        float m_Duration = 0.f;
        EasingFunction m_EasingFunction = EasingCallbacks::linear;
    };
}
