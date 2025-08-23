#include "Lua/CoreLuaInterface.h"
#include "Core/Application.h"
#include "Core/Input.h"

namespace VisionGal
{
	namespace Lua
	{
		void ApplicationLuaInterface::ApplicationQuit()
		{
			Application::Quit();
		}

		void ApplicationLuaInterface::ApplicationOpenURL(const std::string& url)
		{
			Application::OpenURL(url);
		}

		void ApplicationLuaInterface::Initialize(sol::state& lua)
		{
			sol::table game = lua.create_named_table("Application");
			game.set_function("Quit", ApplicationQuit);
			game.set_function("OpenURL", ApplicationOpenURL);
		}

		int GameBindString()
		{
			return 0;
		}

		void DataBindingLuaInterface::Initialize(sol::state& lua)
		{
			//	luabridge::getGlobalNamespace(L)
			//		.beginNamespace("Game")
			//		.addFunction("BindString", GameBindString)  // 注册 C 风格函数
			//		.endNamespace();
		}

		void InputLuaInterface::Initialize(sol::state& lua)
		{
			sol::table game = lua.create_named_table("Input");
			game.set_function("GetMouseButtonDown", Input::GetMouseButtonDown);
			game.set_function("GetMouseButtonUp", Input::GetMouseButtonUp);
			game.set_function("GetMouseButtonHeld", Input::GetMouseButtonHeld);
			game.set_function("GetKeyName", Input::GetKeyName);
			game.set_function("GetKeyNameDown", Input::GetKeyNameDown);
			game.set_function("GetKeyNameUp", Input::GetKeyNameUp);
		}
	}

	void CoreLuaInterface::Initialize(sol::state& L)
	{
		Lua::InputLuaInterface::Initialize(L);
		Lua::ApplicationLuaInterface::Initialize(L);
	}
}


