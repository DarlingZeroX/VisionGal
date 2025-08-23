#include "Interface/GameInterface.h"

namespace VisionGal
{
	ICamera::~ICamera()
	{
		for (auto viewport: m_Viewports)
		{
			viewport->RemoveCamera(this);
		}
	}

	void ICamera::AttachViewport(IViewport* viewport)
	{
		m_Viewports.push_back(viewport);
	}
}
