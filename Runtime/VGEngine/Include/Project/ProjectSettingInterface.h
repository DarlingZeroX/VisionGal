#pragma once
#include <HCore/Include/File/NlohmannJson.h>

namespace VisionGal
{
	struct ProjectSettingInterface
	{
		virtual ~ProjectSettingInterface() = default;

		virtual void Load(const nlohmann::json& json) = 0;
		virtual void Save(nlohmann::json& json) = 0;
	};

}
