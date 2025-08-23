#include "LuaDocument.h"
#include <RmlUi/Core/Stream.h>
#include <UI/Sol/Interpreter.h>

namespace RmlSol {

	LuaDocument::LuaDocument(const Rml::String& tag) : ElementDocument(tag) {}

	void LuaDocument::LoadInlineScript(const Rml::String& context, const Rml::String& source_path, int source_line)
	{
		Rml::String buffer;
		buffer += "--";
		buffer += source_path;
		buffer += ":";
		buffer += Rml::ToString(source_line);
		buffer += "\n";
		buffer += context;
		Interpreter::DoString(buffer, buffer);
	}

	void LuaDocument::LoadExternalScript(const Rml::String& source_path)
	{
		Interpreter::LoadFile(source_path);
	}
}
