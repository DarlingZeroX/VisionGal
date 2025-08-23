#pragma once
#include "../EngineConfig.h"
#include "../Core/Core.h"

namespace VisionGal
{
	using VGObjectPtr = Ref<VGObject>;

	VG_ENGINE_API VGObjectPtr StaticLoadObject(const String& path, const type_info& typeInfo);

	template<class T>
	inline Ref<T> LoadObject(const String& path)
	{
		return std::dynamic_pointer_cast<T>(StaticLoadObject(path, typeid(T)));
		//return dynamic_cast<Ref<T>>( StaticLoadObject(uuid, typeid(T)) );
	}

	struct VGObjectLoader
	{
		virtual ~VGObjectLoader() = default;

		virtual VGObjectPtr StaticLoadObject(const String& path) = 0;
	};

	VG_ENGINE_API int RegisterObjectLoader(const type_info& typeInfo, VGObjectLoader* loader);
}