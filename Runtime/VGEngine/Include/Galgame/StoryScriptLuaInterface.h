#pragma once
#include "../Lua/sol2/sol.hpp"

namespace VisionGal::GalGame
{
	struct StoryScriptLuaInterface
	{
		static int Continue();

		static void SetStoryScriptCoroutine(sol::coroutine* co);
		static sol::coroutine* GetStoryScriptCoroutine();
		//
		//	static void Initialise(lua_State* L);
		//
		static void Initialise(sol::state& lua);
	};
}
