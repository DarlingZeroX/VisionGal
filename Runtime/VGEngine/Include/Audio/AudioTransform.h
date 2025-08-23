#pragma once
#include "../Interface/GameInterface.h"
#include "../Game/TransformProperty.h"

namespace VisionGal
{
    struct AudioTransformState {
        AudioTransformState();
        ~AudioTransformState() = default;

        struct TransformData
        {
            float volume = 1.f;
            bool visible = true;
        };

        TransformProperty volume;
        TransformProperty visible; // 将bool转为float(0.0/1.0)

        // 立即设置所有属性值
        void SetAll(const TransformData& data);
        void SetAll(const AudioTransformState& data);

        void Finish();
        bool IsFinish();
        void Reset();
		 
        void TravelProperty(std::function<void(TransformProperty& property)> callback);

        // 获取当前状态（转换为原始格式）
        TransformData GetCurrent() const;
    };

    class AudioTransformScript : public ITransformScript
    {
    public:
        AudioTransformScript() = default;
        ~AudioTransformScript() override = default;
        AudioTransformScript(const AudioTransformScript&) = delete;
        AudioTransformScript& operator=(const AudioTransformScript&) = delete;
        AudioTransformScript(AudioTransformScript&&) noexcept = default;
        AudioTransformScript& operator=(AudioTransformScript&&) noexcept = default;

        // 为单个属性设置动画
        void TransformVolume(float startTime, float duration, float startVal = 1.0f, float endVal = 1.0f, EasingFunction easing = EasingCallbacks::linear);
        void TransformVisible(float startTime, float duration, bool startVal = true, float endVal = true, EasingFunction easing = EasingCallbacks::linear);

        void Reset();
        void Finish();

        void OnUpdate(Horizon::HEntityInterface* entity) override;
        void OnFixUpdate(Horizon::HEntityInterface* entity) override;

    private:
        void ApplyStateToEntity(Horizon::HEntityInterface* entity);
        float GetCurrentTime() const;

        AudioTransformState state;
    };


}
