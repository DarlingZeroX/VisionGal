#include "SolPlugin.h"
#include <RmlUi/Core/Factory.h>
#include <RmlUi/Core/FileInterface.h>
#include <RmlUi/Core/Log.h>
#include "Types.h"

namespace RmlSol {

	static sol::state* g_L = nullptr;

	SolPlugin::SolPlugin(sol::state* lua_state)
	{
		RMLUI_ASSERT(g_L == nullptr);
		g_L = lua_state;
	}

	int SolPlugin::GetEventClasses()
	{
		return Rml::Plugin::EVT_BASIC;
	}

	void SolPlugin::OnInitialise()
	{
		if (g_L == nullptr)
		{
			Rml::Log::Message(Rml::Log::LT_INFO, "Loading Lua plugin using a new Lua state.");
			g_L = new sol::state();
			g_L->open_libraries(sol::lib::base,
				sol::lib::math,
				sol::lib::string,
				sol::lib::table); // Ĭ���Ѽ�����Щ��
			owns_lua_state = true;
		}
		else
		{
			Rml::Log::Message(Rml::Log::LT_INFO, "Loading Lua plugin using the provided Lua state.");
			owns_lua_state = false;
		}
		RegisterTypes();

		lua_document_element_instancer = new LuaDocumentElementInstancer();
		lua_event_listener_instancer = new LuaEventListenerInstancer();
		Rml::Factory::RegisterElementInstancer("body", lua_document_element_instancer);
		Rml::Factory::RegisterEventListenerInstancer(lua_event_listener_instancer);
	}

	void SolPlugin::OnShutdown()
	{
		g_L = nullptr;

		delete this;
	}

	void SolPlugin::RegisterTypes()
	{
		RMLUI_ASSERT(g_L);
		sol::state* L = g_L;

		RmlSolInitTypes(L);
	}

	sol::state* SolPlugin::GetLuaState()
	{
		return g_L;
	}
}
