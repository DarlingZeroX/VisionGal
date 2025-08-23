#pragma once
#include "IncludeHeader.h"

namespace RmlSol {

	struct RmlRmlUI
	{
		static void RegisterType(sol::state* lua, sol::table& rml);

		static void CreateKeyIdentifierTable(sol::table& rml);
		static void CreateKeyModifierTable(sol::table& rml);
	};


}
