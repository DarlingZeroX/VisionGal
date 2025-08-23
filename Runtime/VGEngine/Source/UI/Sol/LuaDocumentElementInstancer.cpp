#include "LuaDocumentElementInstancer.h"
#include "LuaDocument.h"

namespace RmlSol {

/// Instances an element given the tag name and attributes.
/// @param[in] parent The element the new element is destined to be parented to.
/// @param[in] tag The tag of the element to instance.
/// @param[in] attributes Dictionary of attributes.
Rml::ElementPtr LuaDocumentElementInstancer::InstanceElement(Rml::Element* /*parent*/, const Rml::String& tag, const Rml::XMLAttributes& /*attributes*/)
{
	return Rml::ElementPtr(new LuaDocument(tag));
}
/// Releases an element instanced by this instancer.
/// @param[in] element The element to release.
void LuaDocumentElementInstancer::ReleaseElement(Rml::Element* element)
{
	delete element;
}

}
