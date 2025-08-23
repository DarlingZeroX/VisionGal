#include "Lua/LuaInterface.h"		
#include "Lua/CoreLuaInterface.h"
#include "Lua/SceneLuaInterface.h"
#include "Lua/RenderLuaInterface.h"

namespace VisionGal
{
	void VGLuaInterface::Initialise(sol::state& L)
	{
		CoreLuaInterface::Initialize(L);
		SceneLuaInterface::Initialize(L);
		RenderLuaInterface::Initialize(L);
	}
}


