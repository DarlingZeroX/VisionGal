#pragma once
#include "../Lua/sol2/sol.hpp"

namespace VisionGal
{
	namespace Lua
	{
		struct ApplicationLuaInterface
		{
			static void ApplicationQuit();
			static void ApplicationOpenURL(const std::string& url);

			static void Initialize(sol::state& L);
		};

		struct DataBindingLuaInterface
		{
			static void Initialize(sol::state& L);
		};

		struct InputLuaInterface
		{
			static void Initialize(sol::state& L);
		};
	}

	struct CoreLuaInterface
	{
		static void Initialize(sol::state& L);
	};
}