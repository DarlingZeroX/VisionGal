#include "EditorComponents/DetailBrowser/Browser.h"
#include "EditorComponents/DetailBrowser/ComponentDrawer.h"
#include "EditorCore/Localization.h"
#include <VGEngine/Include/Core/EventBus.h>
#include <VGImgui/IncludeImGui.h>
#include <HCore/Include/Core/HStringTools.h>

#include "VGEngine/Include/Lua/LuaScript.h"
#include "VGImgui/Include/ImGuiEx/ImGuiEx.h"
#include "VGImgui/Include/ImGuiEx/ImNotify.h"

namespace VisionGal::Editor {

	DetailBrowserPanel::DetailBrowserPanel()
	{
		m_DrawerManager.RegisterDrawer(CreateRef<TransformComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<CameraComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<SpriteRendererComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<GalGameEngineComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<ScriptComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<AudioSourceComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<VideoPlayerComponentDrawer>());
		m_DrawerManager.RegisterDrawer(CreateRef<RmlUIDocumentComponentDrawer>());

		SubscribeEngineEvent();
		SubscribeSceneEvent();
	}

	void DetailBrowserPanel::OnGUI()
	{
		if (!m_IsOpen)
			return;

		if (m_pScene == nullptr)
			return;

		if (ImGui::Begin(GetWindowFullName().c_str()))
		{
			auto* selectedEntity = m_pScene->GetEntity(m_SelectEntityID);
			if (m_SelectEntityID == 0 || selectedEntity == nullptr)
			{
				ImGui::Separator();
				ImGui::SameLine(5);
				ImGui::Text(EditorText{ "Select a game object to view details." }.c_str());

				ImGui::End();
				return;
			}

			//auto& registry = m_rScene.GetWorld();
			auto* entityObject = selectedEntity->GetComponent<Horizon::HEntityObjectData>();
			auto* relation = selectedEntity->GetComponent<Horizon::HRelationship>();

			if (entityObject != nullptr && entityObject->ComponentTypes.size() > 0)
			{
				//ImGui::TextWrapped(relation->Label.c_str());
				ImGui::Text(EditorText{ "Label" }.c_str());
				ImGui::SameLine();
				ImGuiEx::InputText("##DetailBrowserPanelActorLabel", relation->Label);

				for (auto& component : entityObject->ComponentTypes)
				{
					m_DrawerManager.GetDrawer(component)->OnGUI(selectedEntity);
				}
			}

			// 1. ��ȡ���ڳߴ�
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 windowSize = ImGui::GetWindowSize();

			// 2. ���������������ڵ�͸����ť�����Ӿ�Ч���������ڽ�����
			ImGui::SetCursorScreenPos(windowPos);
			ImGui::InvisibleButton("##DetailBrowserPanelDragTarget", windowSize);
			BeginDropTarget();
		}

		ImGui::End();
	}

	void DetailBrowserPanel::SubscribeEngineEvent()
	{
		EngineEventBus::Get().OnEngineEvent.Subscribe([this](const EngineEvent& evt)
			{
				switch (evt.EventType)
				{
				case EngineEventType::MainSceneChanged:
					m_pScene = static_cast<Scene*>(evt.Scene);
					break;
				}
			});
	}

	void DetailBrowserPanel::SubscribeSceneEvent()
	{
		EngineEventBus::Get().OnSceneEvent.Subscribe([this](const SceneEvent& evt)
			{
				switch (evt.EventType)
				{
				case SceneEventType::ActorSelected:
				//	m_pSelectedEntity = dynamic_cast<GameActor*>( m_pScene->GetEntity(evt.EntityID) );
					m_SelectEntityID = evt.EntityID;
					break;
				//case SceneEventType::EntityRemoved:
				//	if (m_pSelectedEntity != nullptr && m_pSelectedEntity->GetEntityID() == evt.EntityID)
				//	{
				//		m_pSelectedEntity = nullptr;
				//	}
				}
			});
	}

	void DetailBrowserPanel::BeginDropTarget()
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const auto* payload = ImGui::AcceptDragDropPayload("PLACE_CONTENT_BROWSER_ITEM"))
			{
				std::string path = static_cast<char*>(payload->Data);
				Horizon::HPath hPath = path;
				std::string ext = hPath.extension().string();

				if (ext == ".lua")
				{
					if (auto* selectedEntity = dynamic_cast<GameActor*>( m_pScene->GetEntity(m_SelectEntityID) ))
					{
						if (selectedEntity->GetComponent<ScriptComponent>() == nullptr)
						{
							selectedEntity->AddComponent<ScriptComponent>();
						}

						auto* com = selectedEntity->GetComponent<ScriptComponent>();
						auto script = LuaScript::LoadFromFile(path);
						com->scripts.push_back(script);
					}
				}

				//ImGuiEx::PushNotification({ ImGuiExToastType::Info, "Drag Sprite" });
			}
			ImGui::EndDragDropTarget();
		}
	}

	std::string DetailBrowserPanel::GetWindowFullName()
	{
		return EditorText{ GetWindowName() }.GetText();
	}

	std::string DetailBrowserPanel::GetWindowName()
	{
		return "Details";
	}

	void DetailBrowserPanel::OpenWindow(bool open)
	{
		m_IsOpen = open;
	}

	bool DetailBrowserPanel::IsWindowOpened()
	{
		return m_IsOpen;
	}
}
