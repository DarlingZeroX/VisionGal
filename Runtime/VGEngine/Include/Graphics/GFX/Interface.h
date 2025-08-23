#include "GFX.h"
#include <vector>
#include <iostream>

VISIONGAL_GFX_NAMESPACE_BEGIN

class Bindable
{
public:
	virtual void Bind() const = 0;
	virtual ~Bindable() = default;
};

class Renderable
{
public:
	virtual unsigned int GetRendererID() const noexcept = 0;
	virtual ~Renderable() = default;
};

VISIONGAL_GFX_NAMESPACE_END