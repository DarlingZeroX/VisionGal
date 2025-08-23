#include "pch.h"
#include "System/HLocale.h"
#include <SDL3/SDL_locale.h>

namespace Horizon
{
	void HLocale::GetPreferredLocales(HLocale& locale)
	{
		int count = 0;
		SDL_Locale** sdlLocale = SDL_GetPreferredLocales(&count);

		locale.Country = (*sdlLocale)->country;
		locale.Language = (*sdlLocale)->language;

		SDL_free(sdlLocale);
	}
}