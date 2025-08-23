#include <bgfx/bgfx.h>

#include <HCore/HConfig.h>
#include "../../Core/Core.h"

#ifndef VISIONGAL_GFX_NAMESPACE_BEGIN
#define VISIONGAL_GFX_NAMESPACE_BEGIN namespace VisionGal { namespace GFX {
#endif

#ifndef VISIONGAL_GFX_NAMESPACE_END
#define VISIONGAL_GFX_NAMESPACE_END }}
#endif

#ifndef VISIONGAL_GFX_NAMESPACE
#define VISIONGAL_GFX_NAMESPACE VisionGal::GFX
#endif

VISIONGAL_GFX_NAMESPACE_BEGIN

void Initliaze();

void BeginFrame();

void EndFrame();

void ShutDown();

VISIONGAL_GFX_NAMESPACE_END