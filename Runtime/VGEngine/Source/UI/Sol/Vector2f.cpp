#include "Vector2f.h"
#include <RmlUi/Core/Vector2.h>

namespace RmlSol {

	void RmlVector2f::RegisterType(sol::state* lua)
	{
		// Rml::Vector2f
		lua->new_usertype<Rml::Vector2f>("RmlVector2f",
			sol::constructors<Rml::Vector2f()>(),
			"x", &Rml::Vector2f::x,
			"y", &Rml::Vector2f::y,
			"magnitude", sol::property(
				[](Rml::Vector2f& self) -> float { return self.Magnitude(); }
			),

			"DotProduct", &Rml::Vector2f::DotProduct,
			"Normalise", &Rml::Vector2f::Normalise,
			"Rotate", &Rml::Vector2f::Rotate,

			sol::meta_function::multiplication, [](const Rml::Vector2f& lhs, const Rml::Vector2f& rhs) {
				return lhs * rhs;
			},
			sol::meta_function::division, [](const Rml::Vector2f& lhs, const Rml::Vector2f& rhs) {
				return lhs / rhs;
			},
			sol::meta_function::addition, [](const Rml::Vector2f& lhs, const Rml::Vector2f& rhs) {
				return lhs + rhs;
			},
			sol::meta_function::subtraction, [](const Rml::Vector2f& lhs, const Rml::Vector2f& rhs) {
				return lhs - rhs;
			},
			sol::meta_function::equal_to, [](const Rml::Vector2f& lhs, const Rml::Vector2f& rhs) {
				return lhs == rhs;
			}
		);
	}
}
