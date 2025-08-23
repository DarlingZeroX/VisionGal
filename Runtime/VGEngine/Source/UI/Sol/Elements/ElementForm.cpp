#include "ElementForm.h"
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Elements/ElementForm.h>

namespace RmlSol {

	void RmlElementForm::RegisterType(sol::state* lua)
	{
		// Rml::Colourf
		lua->new_usertype<Rml::ElementForm>("RmlElementForm",
			sol::bases<Rml::Element>(),
			sol::constructors<Rml::ElementForm(const Rml::String&)>(),
			"Submit", &Rml::ElementForm::Submit
		);

	}
}
