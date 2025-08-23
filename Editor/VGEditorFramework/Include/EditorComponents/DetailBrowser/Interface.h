#pragma once
#include "../../Config.h"
#include <VGEngine/Include/Interface/SceneInterface.h>

namespace VisionGal::Editor {

	struct IComponentDrawer
	{
		virtual ~IComponentDrawer() = default;

		virtual void OnGUI(IEntity* entity) = 0;
		virtual const String GetBindType() const = 0;
	};
}