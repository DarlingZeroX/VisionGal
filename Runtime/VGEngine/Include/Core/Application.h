#pragma once
#include "../EngineConfig.h"
#include <string>

namespace VisionGal
{
	struct VG_ENGINE_API Application
	{
	 	static void Quit();
		
		static void OpenURL(std::string url);
	};
}