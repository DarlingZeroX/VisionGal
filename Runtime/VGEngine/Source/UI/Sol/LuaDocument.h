#pragma once
/*
    This class is an ElementDocument that overrides the LoadInlineScript and LoadExternalScript function
*/
#include <RmlUi/Core/ElementDocument.h>

namespace RmlSol {

	class LuaDocument : public ::Rml::ElementDocument {
	public:
		LuaDocument(const Rml::String& tag);
		void LoadInlineScript(const Rml::String& content, const Rml::String& source_path, int source_line) override;
		void LoadExternalScript(const Rml::String& source_path) override;
	};

}
