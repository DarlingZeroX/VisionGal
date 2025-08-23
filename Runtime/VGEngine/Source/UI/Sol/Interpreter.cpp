#include "SolPlugin.h"
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/FileInterface.h>
#include <RmlUi/Core/Log.h>
#include "UI/Sol/Interpreter.h"

namespace RmlSol {
	sol::state* Interpreter::GetLuaState()
	{
		return SolPlugin::GetLuaState();
	}

	bool Interpreter::LoadFile(const Rml::String& file)
	{
		// use the file interface to get the contents of the script
		Rml::FileInterface* file_interface = Rml::GetFileInterface();
		Rml::FileHandle handle = file_interface->Open(file);
		if (handle == 0)
		{
			Rml::Log::Message(Rml::Log::LT_WARNING, "LoadFile: Unable to open file: %s", file.c_str());
			return false;
		}

		size_t size = file_interface->Length(handle);
		if (size == 0)
		{
			Rml::Log::Message(Rml::Log::LT_WARNING, "LoadFile: File is 0 bytes in size: %s", file.c_str());
			return false;
		}
		Rml::UniquePtr<char[]> file_contents(new char[size]);
		file_interface->Read(file_contents.get(), size, handle);
		file_interface->Close(handle);

		DoString(file_contents.get());
	}

	bool Interpreter::DoString(const Rml::String& code, const Rml::String& name)
	{
		sol::state* L = GetLuaState();

		bool noError = true;

		try {
			auto result = L->safe_script(code, sol::script_pass_on_error);
			if (result.valid()) {
				noError = true;
			}
			else {
				sol::error err = result;
				H_LOG_ERROR("%s Error: %s", name.c_str(), err.what());
				noError = false;
			}
		}
		catch (const sol::error& e) {
			noError = false;
			H_LOG_ERROR("%s Error: %s", name.c_str(), e.what());
		}

		return noError;
	}

	bool Interpreter::LoadFunction(sol::function& function, const Rml::String& code, const Rml::String& name)
	{
		sol::state* L = GetLuaState();

		bool noError = true;

		try {
			function = L->safe_script(code, sol::script_pass_on_error);
			if (function.valid()) {
				noError = true;
			}
			else {
				H_LOG_ERROR("%s Load Lua Function Error", name.c_str());
				noError = false;
			}
		}
		catch (const sol::error& e) {
			noError = false;
			H_LOG_ERROR("%s Error: %s", name.c_str(), e.what());
		}

		return noError;
	}
}
