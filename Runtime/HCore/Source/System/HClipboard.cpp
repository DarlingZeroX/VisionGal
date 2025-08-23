﻿#include "pch.h"
#include "System/HClipboard.h"
#include <SDL3/SDL_clipboard.h>

namespace Horizon
{
	int HClipboard::SetText(const char* text)
	{
		return SDL_SetClipboardText(text);
	}

	std::string HClipboard::GetText()
	{
		char* text = SDL_GetClipboardText();

		std::string result = text;

		// Get UTF-8 text from the clipboard, which must be freed with SDL_free().
		SDL_free(text);

		return result;
	}

	bool HClipboard::HasText()
	{
		return SDL_HasClipboardText();
	}
}