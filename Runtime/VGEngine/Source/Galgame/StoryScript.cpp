#include "Galgame/StoryScript.h"
#include "Core/Core.h"
#include "Galgame/StoryScriptLuaInterface.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <HCore/Include/Core/HLog.h>
#include "Core/VFS.h"
#include "Galgame/GalGameEngine.h"
#include "Galgame/GameEngineCore.h"
#include "Lua/sol2/sol.hpp"

namespace VisionGal::GalGame
{
    LuaStoryScript::LuaStoryScript()
    {
        StoryScriptLuaInterface::Initialise(m_LuaState);
    }

    Ref<LuaStoryScript> LuaStoryScript::LoadFromFile(const std::string& file)
    {
        Ref<LuaStoryScript> script = CreateRef<LuaStoryScript>();

        script->SetResourcePath(file);

        return script;
    }

    bool LuaStoryScript::Run(IGalGameEngine* engine)
    {
        m_LuaState["Engine"] = sol::object(m_LuaState, sol::in_place, dynamic_cast<GalGameEngine*>(engine));
        m_LuaState["引擎"] = sol::object(m_LuaState, sol::in_place, dynamic_cast<GalGameEngine*>(engine));

        if (!LoadScript(GetResourcePath()))
            return false;

        StoryScriptLuaInterface::SetStoryScriptCoroutine(&m_Coroutine);

        PreLoadScriptResource();

    	auto result = m_Coroutine();
    
        if (m_Coroutine.error())
        {
            sol::error err = result;
            std::string errorStr = err.what();
            H_LOG_ERROR(err.what());
            return false;
        }

        return true;
    }

    void LuaStoryScript::PreLoadScriptResource()
    {
        std::istringstream inputStream(m_ScriptCode);
        std::string line;

        std::set<std::string> resourcePaths;

        std::regex resourceRegex(R"(['"]([^'"]+\.(png|jpg|jpeg|tga|bmp|wav|mp3|ogg))['"])");
        std::smatch match;

        // 根据正则表达式识别资源
        while (std::getline(inputStream, line)) {
            auto begin = line.cbegin();
            auto end = line.cend();

            while (std::regex_search(begin, end, match, resourceRegex)) {
                resourcePaths.insert(match[1].str());
                begin = match.suffix().first;
            }
        }

        // 预加载资源
        for (const auto& path : resourcePaths) {
            GameEngineCore::GetCurrentEngine()->PreLoadResource(path);
        }
    }

    bool LuaStoryScript::LoadScript(const String& file)
    {
		auto result = VFS::ReadTextFromFile(file, m_ScriptCode);

		if (!result)
		{
			H_LOG_ERROR("Failed to read story script file: %s", file.c_str());
			return false;
		}

        try {
            m_Coroutine = m_LuaState.script(m_ScriptCode);
        }
        catch (const sol::error& e) {
            H_LOG_ERROR(e.what());

            return false;
        }

        return true;
    }
}
