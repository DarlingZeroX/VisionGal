#include "Lua/LuaScript.h"
#include "Core/VFS.h"
#include "Lua/LuaInterface.h"

namespace VisionGal
{
	Ref<LuaScript> LuaScript::LoadFromFile(const String& file)
	{
		auto script = CreateRef<LuaScript>();

		auto result = VFS::ReadTextFromFile(file, script->m_ScriptString);

		if (!result)
			return nullptr;

		script->SetResourcePath(file);
		script->m_ScriptPath = file;
		script->Initialize();

		return script;
	}

	void LuaScript::Initialize()
	{
		m_LuaState.open_libraries(sol::lib::base,
			sol::lib::math,
			sol::lib::string,
			sol::lib::table); // 默认已加载这些库
		VGLuaInterface::Initialise(m_LuaState);

		m_IsError = false;

		try {
			auto result = m_LuaState.safe_script(m_ScriptString, sol::script_pass_on_error);
			if (result.valid()) {
				m_Script = result;
			}
			else {
				sol::error err = result;
				H_LOG_ERROR("%s Error: %s", m_ScriptPath.c_str(), err.what());
				m_IsError = true;
			}
		}
		catch (const sol::error& e) {
			m_IsError = true;
			H_LOG_ERROR("%s Error: %s", m_ScriptPath.c_str(), e.what());
		}

		if (m_IsError == false)
		{
			m_StartFunction = m_Script["Start"];
			m_UpdateFunction = m_Script["Update"];

			ReadScriptVariables();
		}
	}

	Ref<LuaScript> LuaScript::Reload()
	{
		return LoadFromFile(this->m_ScriptPath);
	}

	void LuaScript::ReadScriptVariables()
	{
		// 遍历并存储变量
		m_Script.for_each([&](sol::object key, sol::object value) {
			std::string name = key.as<std::string>();
			if (name == "_G" || name == "_VERSION")// 排除特定内置变量
				return; 
			if (value.get_type() == sol::type::function || value.get_type() == sol::type::thread)
				return;

			IScriptVariable var;
			var.VariableName = name;
			var.NativeType = int(value.get_type());

			switch (value.get_type())
			{
			case sol::type::string:
				var.VariableType = "String";
				var.ValueString = value.as<std::string>();
				break;
			case sol::type::number:
				var.VariableType = "Number";
				var.ValueDouble = value.as<double>();
				break;
			case sol::type::boolean:
				var.VariableType = "Boolean";
				var.ValueDouble = value.as<bool>();
				break;
			default: break;
			}

			m_Variables[name] = var;
			
		});
	}

	String LuaScript::GetScriptType()
	{
		return "LuaScript";
	}

	void LuaScript::Awake(GameActor* actor)
	{
		if (m_IsError)
			return;

		for (auto& var : m_Variables)
		{
			auto& v = var.second;
			if (v.VariableType == "Number")
			{
				m_Script[v.VariableName] = sol::object(m_LuaState, sol::in_place, v.ValueDouble);;
			}
			else if (v.VariableType == "String")
			{
				m_Script[v.VariableName] = sol::object(m_LuaState, sol::in_place, v.ValueString);;
			}
			else if (v.VariableType == "Boolean")
			{
				m_Script[v.VariableName] = sol::object(m_LuaState, sol::in_place, v.ValueBoolean);;
			}
			else if (v.VariableType == "GameActor")
			{
				auto* scene = dynamic_cast<IScene*>(actor->GetScene());
				auto* actor = dynamic_cast<GameActor*>(scene->GetEntity(v.ValueEntityID));
				if (actor)
				{
					m_Script[v.VariableName] = sol::object(m_LuaState, sol::in_place, actor);
				}
			}
		}

		m_Script["gameObject"] = sol::object(m_LuaState, sol::in_place, actor);
	}

	void LuaScript::Start(GameActor* actor)
	{
		// 检查函数是否有效
		if (!m_StartFunction.valid()) {
			H_LOG_ERROR("LuaScript::Start: m_StartFunction is not valid");
			return;
		}

		if (m_StartFunction)
		{

			//m_StartFunction(actor);
			// 使用安全调用的方式
			sol::protected_function_result result = m_StartFunction(m_Script);
			if (!result.valid()) {
				sol::error err = result;
				H_LOG_ERROR("%s Error: %s", m_ScriptPath.c_str(), err.what());
			}
		}
	}

	void LuaScript::Update(GameActor* actor, float deltaTime)
	{
		// 检查函数是否有效
		if (!m_UpdateFunction.valid()) {
			H_LOG_ERROR("LuaScript::Start: m_UpdateFunction is not valid");
			return;
		}

		if (m_StartFunction)
		{
			//m_StartFunction(actor);
			// 使用安全调用的方式
			sol::protected_function_result result = m_UpdateFunction(m_Script, deltaTime);
			if (!result.valid()) {
				sol::error err = result;
				H_LOG_ERROR("%s Error: %s", m_ScriptPath.c_str(), err.what());
			}
		}
	}

	void LuaScript::FixedUpdate(GameActor* actor)
	{

	}

	void LuaScript::SetVariable(IScriptVariable& variable)
	{

	}

	void LuaScript::SetVariable(const ScriptVariableTable& variables)
	{
		m_Variables = variables;
	}
}
