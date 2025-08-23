#include "Event.h"
#include <RmlUi/Core/Event.h>
#include <RmlUi/Core/Element.h>
#include "UI/Sol/Utilities.h"

namespace RmlSol {

	struct RmlEventParametersProxy {
		Rml::Event* owner;
	};

	void RmlEvent::RegisterType(sol::state* lua)
	{
		// Rml::Event
		lua->new_usertype<Rml::Event>("RmlEvent",
			sol::constructors<Rml::Event()>(),
			"StopPropagation", &Rml::Event::StopPropagation,
			"StopImmediatePropagation", &Rml::Event::StopImmediatePropagation,
			"type", sol::property(
				[](Rml::Event& self) ->const Rml::String& { return self.GetType(); }
			),
			"currentElement", sol::property(
				[](Rml::Event& self) ->Rml::Element* { return self.GetCurrentElement(); }
			),
			"targetElement", sol::property(
				[](Rml::Event& self) ->Rml::Element* { return self.GetTargetElement(); }
			),
			"parameters", sol::property(
				[](Rml::Event& self) -> RmlEventParametersProxy
				{
					RmlEventParametersProxy proxy;
					proxy.owner = &self;
					return proxy;
				}
			),
			"isPropagating", sol::property(
				[](Rml::Event& self) { return self.IsPropagating(); }
			),
			"isImmediatePropagating", sol::property(
				[](Rml::Event& self) { return self.IsImmediatePropagating(); }
			),
			"isInterruptible", sol::property(
				[](Rml::Event& self) { return self.IsInterruptible(); }
			)
		);

		lua->new_usertype<RmlEventParametersProxy>("RmlEventParametersProxy",
			sol::meta_function::index, [](RmlEventParametersProxy& self, const std::string& key, sol::this_state lua) {
				auto it = self.owner->GetParameters().find(key);
				const Rml::Variant* param = (it == self.owner->GetParameters().end() ? nullptr : &it->second);

				if (self.owner->GetId() == Rml::EventId::Tabchange && key == "tab_index" && param && param->GetType() == Rml::Variant::Type::INT)
				{
					return PushIndex(lua, param->Get<int>());
				}
				else
				{
					return PushVariant(lua, param);
				}
			});
	}
}
