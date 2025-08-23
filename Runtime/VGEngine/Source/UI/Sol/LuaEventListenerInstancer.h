#pragma once
#include <RmlUi/Core/EventListenerInstancer.h>

namespace RmlSol {

	class LuaEventListenerInstancer : public ::Rml::EventListenerInstancer {
	public:
		/// Instance an event listener object.
		/// @param value Value of the event.
		/// @param element Element that triggers the events.
		Rml::EventListener* InstanceEventListener(const Rml::String& value, Rml::Element* element) override;
	};
}
