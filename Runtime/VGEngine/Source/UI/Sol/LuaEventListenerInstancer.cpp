#include "LuaEventListenerInstancer.h"
#include "LuaEventListener.h"

namespace RmlSol {

	/// Instance an event listener object.
	/// @param value Value of the event.
	/// @param element Element that triggers the events.
	Rml::EventListener* LuaEventListenerInstancer::InstanceEventListener(const Rml::String& value, Rml::Element* element)
	{
		return new LuaEventListener(value, element);
	}

}
