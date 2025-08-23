#pragma once
#include "Events.h"
#include <HCore/Include/Event/HEventDelegate.h>

namespace VisionGal
{
	struct VG_ENGINE_API EngineEventBus
	{
		//Horizon::HEventDelegate<const TransformUpdateEvent&> OnTransformUpdateEvent;

		Horizon::HEventDelegate<const SceneEvent&> OnSceneEvent;

		Horizon::HEventDelegate<const EngineEvent&> OnEngineEvent;

		static EngineEventBus& Get();
	};

}