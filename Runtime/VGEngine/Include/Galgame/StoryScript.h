#pragma once
#include "GalGameEngineInterface.h"
#include "../Core/Core.h"
#include "../Lua/sol2/sol.hpp"

namespace VisionGal::GalGame
{
	class VG_ENGINE_API LuaStoryScript : public VGEngineResource
	{
	public:
		LuaStoryScript();
		~LuaStoryScript() override = default;

		static Ref<LuaStoryScript> LoadFromFile(const String& file);
		bool Run(IGalGameEngine* engine);

		sol::coroutine GetCoroutine() { return m_Coroutine; }
		void PreLoadScriptResource();
	private:
		bool LoadScript(const String& file);
	private:
		String m_ScriptCode;
		sol::state m_LuaState;
		sol::coroutine m_Coroutine;
	};
}