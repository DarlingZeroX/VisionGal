#pragma once
#include <string>
#include <VGImgui/Include/ImGuiEx/ImPanelInterface.h>

namespace VisionGal::Editor {

	struct IPanel 
	{
		virtual ~IPanel() = default;

		virtual void OnUpdate(float delta) {};
		virtual void OnFixedUpdate() {};
		virtual bool IsAsync() { return false; }
		virtual void OnGUI() {};
	};

	struct IEditorPanel: public IPanel
	{
		virtual std::string GetWindowFullName() = 0;
		virtual std::string GetWindowName() = 0;
		virtual void OpenWindow(bool open) = 0;
		virtual bool IsWindowOpened() = 0;
	};

	struct ISidebarComponent: public IPanel
	{
		~ISidebarComponent() override = default;

		virtual void Toggle() = 0;
		virtual void OnSideBarUI() = 0;
	};

}