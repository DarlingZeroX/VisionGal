#pragma once
#include "../EngineConfig.h"
#include "../Core/Core.h"
#include <RmlUi/Core.h>

namespace VisionGal
{
	class VG_ENGINE_API RmlUIDocument : public VGEngineResource
	{
	public:
		RmlUIDocument();
		~RmlUIDocument() override;

		void Close();

		Rml::ElementDocument* document = nullptr;
		bool isClosed = false;
	};
}


