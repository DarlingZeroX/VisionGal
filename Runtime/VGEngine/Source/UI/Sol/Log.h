#pragma once
#include "IncludeHeader.h"

namespace RmlSol {

	struct RmlLog
	{
		static void RegisterType(sol::state* lua, sol::table& rml);
	};

}
