#pragma once
#include "../EngineConfig.h"
#include "../Interface/SceneInterface.h"

namespace VisionGal
{
	////////////////		Engine Event
	enum class EngineEventType
	{
		None = 0,
		MainSceneChanged,
		EnterScenePlayMode,
		ExitScenePlayMode
	};

	struct EngineEvent
	{
		EngineEventType EventType = EngineEventType::None;
		IScene* Scene = nullptr;
		IScene* PrevScene = nullptr;
	};

	////////////////		Scene Event
	enum class SceneEventType
	{
		None = 0,
		EntityCreating,
		EntityRemoved,
		ActorSelected
	};

	struct SceneEvent
	{
		SceneEventType EventType = SceneEventType::None;
		GameActor* Entity = nullptr;
		EntityID EntityID = 0;
	};

	////////////////		 Viewport Event

	enum class ViewportEventType
	{
		None,
		SizeChanged,
		Hovered,

		Focused,
		UnFocused,

		PlacePrefabActor,
		PlaceAsset,
		MouseMove,

		MouseClicked,
		MouseDragging,
	};

	struct ViewportEvent
	{
		ViewportEventType Type;
		float2 NewViewportSize;
		float2 MousePosition;
		String PrefabActorType;
		String  Path;

		ViewportEvent()
			: Type(ViewportEventType::None),
			NewViewportSize(0),
			MousePosition(0)
		{
		}
	};
}