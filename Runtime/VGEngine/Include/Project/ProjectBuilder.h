#pragma once
#include "../EngineConfig.h"
#include <string.h>
#include <filesystem>

namespace VisionGal
{
	struct VG_ENGINE_API ProjectBuilder
	{
		struct BuildContext
		{
			std::filesystem::path OutputDirectory;
			std::string TargetPlatform;
			float process = 0.f;
			bool isError = false;
			std::string errorMessage;
		};

		static bool BuildProject(BuildContext& context);

		static bool CheckBuildSettingIsValid(const BuildContext& context);

		static bool WriteDirectoryToPakFile(const std::filesystem::path& InDirectoryPath, const std::filesystem::path& outPakPath);
	};

}
