#include "pch.h"
#include "Scene/HEntityInterface.h"
#include "Scene/HBaseComponent.h"

namespace Horizon
{
	void* HEntityInterface::GetRelationShip()
	{ 
		return GetComponent<HRelationship>();
	}
}
