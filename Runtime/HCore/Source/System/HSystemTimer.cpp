#include "pch.h"
#include "System/HSystemTimer.h"
#include <SDL3/SDL_timer.h>

namespace Horizon
{
	uint32 HSystemTimer::GetTicks()
	{
		return SDL_GetTicks();
	}

	uint64 HSystemTimer::GetTicks64()
	{
		return SDL_GetTicks();
	}

	uint64 HSystemTimer::GetPerformanceCounter()
	{
		return SDL_GetPerformanceCounter();
	}

	uint64 HSystemTimer::GetPerformanceFrequency()
	{
		return SDL_GetPerformanceFrequency();
	}

	void HSystemTimer::Delay(uint32 ms)
	{
		SDL_Delay(ms);
	}
}