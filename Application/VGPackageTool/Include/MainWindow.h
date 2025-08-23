#pragma once
#include <VGEditorFramework/Include/UIInterface.h>

namespace VisionGal::Editor
{
	/// @brief VGLauncher 主窗口类，用于显示和管理项目列表
	class VGPackageToolMainWindow : public IEditorPanel
	{
	public:
		VGPackageToolMainWindow();
		VGPackageToolMainWindow(const VGPackageToolMainWindow&) = default;
		VGPackageToolMainWindow& operator=(const VGPackageToolMainWindow&) = default;
		VGPackageToolMainWindow(VGPackageToolMainWindow&&) noexcept = default;
		VGPackageToolMainWindow& operator=(VGPackageToolMainWindow&&) noexcept = default;
		~VGPackageToolMainWindow() override = default;

		// 通过 IEditorPanel 继承
		void OnGUI() override;
		void OnUpdate(float delta) override;
		void OnFixedUpdate() override;
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;

	private:
		void OnGUIInternal();
		void RenderLeftUI();
		void RenderRightUI();
	};
}
