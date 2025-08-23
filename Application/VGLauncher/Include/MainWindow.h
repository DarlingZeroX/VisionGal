#pragma once
#include <VGEditorFramework/Include/UIInterface.h>
#include <VGImgui/IncludeImGui.h>

namespace VisionGal::Editor
{
	/// @brief VGLauncher 主窗口类，用于显示和管理项目列表
	class VGLauncherMainWindow : public IEditorPanel
	{
	public:
		VGLauncherMainWindow();
		VGLauncherMainWindow(const VGLauncherMainWindow&) = default;
		VGLauncherMainWindow& operator=(const VGLauncherMainWindow&) = default;
		VGLauncherMainWindow(VGLauncherMainWindow&&) noexcept = default;
		VGLauncherMainWindow& operator=(VGLauncherMainWindow&&) noexcept = default;
		~VGLauncherMainWindow() override = default;

		// 通过 IEditorPanel 继承
		void OnGUI() override;
		void OnUpdate(float delta) override;
		void OnFixedUpdate() override;
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;

		/// @brief 移除一个项目
		/// @param index 索引
		void RemoveProject(int index);

		/// @brief 编辑一个项目
		/// @param index 索引
		void EditProject(int index);
	private:
		void OnGUIInternal();
		void RenderLeftUI();
		void RenderRightUI();
		void RenderProjectItem(int index, const std::string& name, const std::string& path);
		void OpenProjectDialog();

		ImVec2 m_ProjectItemSize;
		int m_SelectProject;
	};


}
