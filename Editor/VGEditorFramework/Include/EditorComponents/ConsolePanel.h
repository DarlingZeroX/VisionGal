#pragma once
#include "../Config.h"
#include <mutex>
#include "HCore/Include/Core/HLog.h"

namespace VisionGal::Editor {

	class VG_EDITOR_FRAMEWORK_API ConsolePanel: public IEditorPanel
	{
	public:
		ConsolePanel();
		ConsolePanel(const ConsolePanel&) = default;
		ConsolePanel& operator=(const ConsolePanel&) = default;
		ConsolePanel(ConsolePanel&&) noexcept = default;
		ConsolePanel& operator=(ConsolePanel&&) noexcept = default;
		~ConsolePanel() override = default;

		void Toggle();
		void OnGUI() override;
		void OnSideBarUI();
		void AddLog(Horizon::HLogLevel level, const std::string& message);

		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;
	private: 
		void RenderLog();
		// 这个函数存在运行随机异常，可能是utf8编码导致的，使用了可变参数列表，避免调用
		void AddLog(const char* fmt, ...);
		void Clear();
	private:

		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		//ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
		std::vector<std::string> m_Lines;
		bool                AutoScroll;  // Keep scrolling if already at the bottom.

		bool m_IsOpen = true;
		std::mutex m_Mutex; // 用于线程安全的日志记录
	};
}
