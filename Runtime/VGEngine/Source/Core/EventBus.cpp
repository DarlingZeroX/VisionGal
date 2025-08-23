#include "Core/EventBus.h"

namespace VisionGal
{
	EngineEventBus& EngineEventBus::Get()
	{
		static EngineEventBus bus;

		return bus;
	}
}
