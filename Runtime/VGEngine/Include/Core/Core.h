#pragma once
#include "CoreTypes.h"
#include "../EngineConfig.h"
#include "../Interface/FileInterface.h"

namespace VisionGal
{
	struct VGObject
	{
		virtual ~VGObject() = default;

		virtual  std::string ToString() { return ""; }
	};

	struct VGEngineResource: public VGObject
	{
		const String& GetResourcePath() { return m_ResourcePath; }
		void SetResourcePath(const String& path) { m_ResourcePath = path; }
	private:
		String m_ResourcePath;
	};

	struct VG_ENGINE_API Core
	{
		static void Initialize();
		static float GetCurrentTime();

		static void SetFileInterface(FileInterface* file_interface);
		static FileInterface* GetFileInterface();

		static std::string GetDefaultSpriteTexturePath();

		static std::string GetAssetsPathVFS();
		static std::string GetProjectIntermediatePathVFS();
		static std::string GetProjectSettingsPathVFS();
		static std::string GetEngineResourcePathVFS();

		static std::filesystem::path GetExecutableDirectory();
	};


}
