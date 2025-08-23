#pragma once
#include <chrono>
#include <functional>

namespace VisionGal
{
	class TransitionHelper {
	public:
		TransitionHelper();
		TransitionHelper(float durationSeconds, std::function<void()> onComplete = nullptr);			// 构造函数：传入总时长和转场完成后的回调函数
		TransitionHelper(const TransitionHelper&) = delete;
		TransitionHelper& operator=(const TransitionHelper&) = delete;
		TransitionHelper(TransitionHelper&&) noexcept = default;
		TransitionHelper& operator=(TransitionHelper&&) noexcept = default;
		~TransitionHelper() = default;

		void SetDuration(float durationSeconds) { duration = durationSeconds; } // 设置转场总时长
		void Reset();
		float Update();		// 更新转场进度（返回 0.0~1.0 之间的进度值）
		bool IsFinished() const;	// 判断转场是否完成
		void Finish();
		float Progress() const;  
	private:
		float duration;                // 转场总时长（秒）
		float progress = 0.0f;         // 当前进度（0.0~1.0）
		std::function<void()> callback; // 转场完成回调函数
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime; // 开始时间
	};
}
 