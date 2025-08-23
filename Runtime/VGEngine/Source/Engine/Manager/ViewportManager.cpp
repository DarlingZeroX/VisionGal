#include "Engine/Manager/ViewportManager.h"

namespace VisionGal
{
	ViewportManager::ViewportManager()
	{
	}

	Viewport* ViewportManager::GetMainViewport()
	{
		return m_MainViewport;
	}

	ViewportManager* ViewportManager::Get()
	{
		static ViewportManager manager;
		return &manager;
	}

	void ViewportManager::SetMainViewport(Viewport* viewport)
	{
		m_MainViewport = viewport;
	}

	Viewport* ViewportManager::NewViewport(float2 size)
	{
		auto viewport = CreateRef<Viewport>(size);

		m_Viewports.push_back(viewport);

		return viewport.get();
	}

	void ViewportManager::FrameUpdate()
	{
		for (auto& viewport : m_Viewports)
		{
			viewport->FrameUpdate();
		}
	}
}


