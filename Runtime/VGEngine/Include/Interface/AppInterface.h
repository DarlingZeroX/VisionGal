#pragma once
#include "EngineInterface.h"
#include "SceneInterface.h"
#include "../Core/Core.h"
#include <HCore/Include/Platform/WindowInterface.h>

namespace VisionGal
{
	struct IGameAppContext
	{
		virtual ~IGameAppContext() = default;

		virtual IUISystem* GetUISystem() = 0;
		virtual Horizon::IWindow* GetWindow() = 0;
		virtual IScene* GetScene() = 0;
	};
}