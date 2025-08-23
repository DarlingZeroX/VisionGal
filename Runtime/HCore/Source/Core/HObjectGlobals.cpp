#include "pch.h"
#include "Core/HObjectGlobals.h"
#include "Core/HTypeInfo.h"

namespace Horizon
{
	static unordered_type_map<Scope<HObjectLoader>> s_ObjectLoaders;

	HObjectPtr StaticLoadObject(const HUUID& uuid, const type_info& typeInfo)
	{
		if(auto result = s_ObjectLoaders.find(&typeInfo); result != s_ObjectLoaders.end())
		{
			return result->second->StaticLoadObject(uuid);
		}

		return nullptr;
	}

	HResult RegisterObjectLoader(const type_info& typeInfo, HObjectLoader* loader)
	{
		s_ObjectLoaders[&typeInfo] = std::unique_ptr<HObjectLoader>(loader);

		return 0;
	}
}
