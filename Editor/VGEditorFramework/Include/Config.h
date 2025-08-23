#pragma once
#include "UIInterface.h"

#if defined(_WIN32) || defined(_WIN64)
#ifdef VG_EDITOR_FRAMEWORK_API_EXPORT
	#define VG_EDITOR_FRAMEWORK_API __declspec(dllexport)
#else
	#define VG_EDITOR_FRAMEWORK_API __declspec(dllimport)
#endif

#else
#ifdef VG_EDITOR_FRAMEWORK_API_EXPORT
	#define VG_EDITOR_FRAMEWORK_API __attribute__((visibility("default")))
#else
	#define VG_EDITOR_FRAMEWORK_API
#endif
#endif



