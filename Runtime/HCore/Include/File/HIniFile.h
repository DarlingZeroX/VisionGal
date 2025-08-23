// Copyright (c) 2025 梦旅缘心
// This file is part of VisionGal and is licensed under the MIT License.
// See the LICENSE file in the project root for details.

#pragma once
#include "../CoreModuleDefinitions.h"
#include "../System/HFileSystem.h"

#include "../Meta/Type.h"
#include "../Core/HTypeInfo.h"

namespace Horizon
{
	class HIniTypeManager;

	class CORE_MODULE_API HIniFile
	{
	public:
		class Internal;

		HIniFile(void);
		HIniFile(Ref<Internal> impl);

		int SaveFileInPath(const fsPath& path);

		static Ref<HIniFile> LoadFromFile(const fsPath& path);

		template<typename T>
		static Ref<HIniFile> CreateFromStruct(const T& data)
		{
			return SerializeType(TypeOf(T), META_NAMESPACE::Variant(data, META_NAMESPACE::VariantPolicy::NoCopy()));
		}

		template<typename T>
		int LoadToStruct(T& data)
		{
			META_NAMESPACE::Variant v(data, META_NAMESPACE::VariantPolicy::NoCopy());
			return DeserializeType(TypeOf(T), v);
		}


	private:
		static Ref<HIniFile> SerializeType(const META_NAMESPACE::Type& type, const META_NAMESPACE::Variant& variant);

		int DeserializeType(const META_NAMESPACE::Type& type, META_NAMESPACE::Variant& variant);

		Ref<Internal> m_Impl;
	};
	
}
