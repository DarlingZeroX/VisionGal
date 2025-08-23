#include "pch.h"
#include "Core/Application.h"
#include "Engine/VGEngine.h"

namespace VisionGal
{
	void Application::Quit()
	{
		VGEngine::Get()->RequestExit();
	}

	void Application::OpenURL(std::string url)
	{

	}
}
