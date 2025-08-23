#include "pch.h"
#include "System/HSystemMisc.h"
#include <SDL3/SDL_misc.h>

namespace Horizon
{
	int HSystemMisc::OpenURL(const char* url)
	{
		return SDL_OpenURL(url);
	}
}