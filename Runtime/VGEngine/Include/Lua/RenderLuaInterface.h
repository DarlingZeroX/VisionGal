#pragma once
#include "../Lua/sol2/sol.hpp"

namespace VisionGal
{
	namespace Lua
	{
		struct TransitionManagerLuaInterface
		{
			static void Initialize(sol::state& L);
		};
	}

	struct RenderLuaInterface
	{
		static void Initialize(sol::state& L);
	};
}