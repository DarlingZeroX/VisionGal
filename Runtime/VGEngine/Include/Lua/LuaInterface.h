#pragma once
#include "../Lua/sol2/sol.hpp"

namespace VisionGal
{
	struct VGLuaInterface
	{
		static void Initialise(sol::state& L);
	};
}