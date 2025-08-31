#include "Engine/EngineResource.h"

namespace VisionGal
{
	std::string EngineResource::GetDefaultSpriteTexturePath()
	{
		std::string path = Core::GetEngineResourcePathVFS() + "textures/white.png";
		return path;
	}
}
