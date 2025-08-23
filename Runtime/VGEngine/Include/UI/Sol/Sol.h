#pragma once
#include "IncludeSol.h"

namespace RmlSol {

	/** Initialise the Lua plugin.
		@remark This is equivalent to calling Initialise(nullptr). */
	RMLUISOL_API void Initialise();

	/** Initialise the Lua plugin and add RmlUi to an existing Lua state if one is provided.
		@remark If nullptr is passed as an argument, the plugin will automatically create the lua state during initialisation
		and close the state during the call to Rml::Shutdown(). Otherwise, if a Lua state is provided, the user is
		responsible for closing the provided Lua state. The state must then be closed after the call to Rml::Shutdown().
		@remark The plugin registers the "body" tag to generate a LuaDocument rather than a ElementDocument. */
	RMLUISOL_API void Initialise(sol::state* L);
} // namespace Rml
