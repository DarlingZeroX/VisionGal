#pragma once
#include "../Config.h"
#include "../EditorCore/MenuItem.h"
#include <VGEngine/Include/Scene/Scene.h>

namespace VisionGal::Editor
{
	class VG_EDITOR_FRAMEWORK_API SceneBrowserPanel : public IEditorPanel
	{
	public:
		SceneBrowserPanel();
		SceneBrowserPanel(const SceneBrowserPanel&) = delete;
		SceneBrowserPanel& operator=(const SceneBrowserPanel&) = delete;
		SceneBrowserPanel(SceneBrowserPanel&&) noexcept = default;
		SceneBrowserPanel& operator=(SceneBrowserPanel&&) noexcept = default;
		~SceneBrowserPanel() override = default;

		// 通过 PanelInterface 继承
		void OnGUI() override;
		 
		std::string GetWindowFullName() override;
		std::string GetWindowName() override;
		void OpenWindow(bool open) override;
		bool IsWindowOpened() override;
	private:
		virtual void DrawHierarchy(GameActor& parent, Horizon::HRelationship& parentRelation);
		bool DrawTreeNodeRow(GameActor& parent);
		bool DrawTreeNodeChildRow(GameActor* currentChild);

		void TickBottomOverlayUI();							// 底部的UI
		void HandleItemHovered(GameActor& entity);			// 当用户鼠标指向这个游戏对象
		bool ItemContextMenu(GameActor& entity);			// 游戏对象右键菜单

		void SubscribeEngineEvent();
		void TriggerSelectedEvent(GameActor& entity);		// 发送选中事件

		void PanelContextMenu();							// 场景浏览器上下文菜单
		void CreateGameActor(const String& type, IEntity* parent = nullptr) const;
	private:
		EntityID m_SelectedEntityID = 0;
		Scene* m_rScene;

		EditorUIMenu m_Menu;
		bool m_IsAnyItemHovered = false;
		bool m_IsOpen = true;
	};

}
