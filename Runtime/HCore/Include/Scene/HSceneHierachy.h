#pragma once
#include "../CoreModuleDefinitions.h"
#include "HSceneInterface.h"
#include "HBaseComponent.h"

namespace Horizon
{
	struct CORE_MODULE_API HHierarchy
	{
		static bool DisconnectParent(HECS& registry, HEntityInterface& child, HRelationship& childInfo);

		static bool SetParent(HECS& registry, HEntityInterface& child, HEntityInterface* parent);	

		static bool SetNextSibling(HECS& registry, HEntityInterface* current, HEntityInterface* next);
	};
}