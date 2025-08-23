#include "Interface/Loader.h"
#include <HCore/Include/Core/HTypeInfo.h>

namespace VisionGal
{
	static Horizon::unordered_type_map<Scope<VGObjectLoader>> s_ObjectLoaders;

	VGObjectPtr StaticLoadObject(const String& path, const type_info& typeInfo)
	{
		if (auto result = s_ObjectLoaders.find(&typeInfo); result != s_ObjectLoaders.end())
		{
			return result->second->StaticLoadObject(path);
		}

		return nullptr;
	}

	int RegisterObjectLoader(const type_info& typeInfo, VGObjectLoader* loader)
	{
		s_ObjectLoaders[&typeInfo] = std::unique_ptr<VGObjectLoader>(loader);

		return 0;
	}
}