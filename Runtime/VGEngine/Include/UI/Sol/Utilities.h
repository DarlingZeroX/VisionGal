#pragma once
#include "IncludeSol.h"
#include <RmlUi/Core/Variant.h>

namespace RmlSol {

	/** casts the variant to its specific type before pushing it to the stack
	@relates LuaType */
	sol::object RMLUISOL_API PushVariant(sol::this_state& L, const Rml::Variant* var);

	// Converts index from 0-based to 1-based before pushing it to the stack
	sol::object RMLUISOL_API PushIndex(sol::this_state& L, int index);
}
