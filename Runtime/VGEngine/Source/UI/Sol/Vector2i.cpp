#include "Vector2i.h"
#include <RmlUi/Core/Vector2.h>

namespace RmlSol {

	void RmlVector2i::RegisterType(sol::state* lua)
	{
		// Rml::Vector2i
		lua->new_usertype<Rml::Vector2i>("RmlVector2i",
			sol::constructors<Rml::Vector2i()>(),
			"x", &Rml::Vector2i::x,
			"y", &Rml::Vector2i::y,
			"magnitude", sol::property(
				[](Rml::Vector2i& self) -> float { return self.Magnitude(); }
			),

			sol::meta_function::multiplication, [](const Rml::Vector2i& lhs, const Rml::Vector2i& rhs) {
				return lhs * rhs;
			},
			sol::meta_function::division, [](const Rml::Vector2i& lhs, const Rml::Vector2i& rhs) {
				return lhs / rhs;
			},
			sol::meta_function::addition, [](const Rml::Vector2i& lhs, const Rml::Vector2i& rhs) {
				return lhs + rhs;
			},
			sol::meta_function::subtraction, [](const Rml::Vector2i& lhs, const Rml::Vector2i& rhs) {
				return lhs - rhs;
			},
			sol::meta_function::equal_to, [](const Rml::Vector2i& lhs, const Rml::Vector2i& rhs) {
				return lhs == rhs;
			}
		);
	}
}
