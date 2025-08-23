#pragma once

#if defined(_WIN32) || defined(_WIN64)
#ifdef VG_PACKAGE_API_EXPORT
#define VG_PACKAGE_API __declspec(dllexport)
#else
#define VG_PACKAGE_API __declspec(dllimport)
#endif

#else
#ifdef VG_PACKAGE_API_EXPORT
#define VG_PACKAGE_API __attribute__((visibility("default")))
#else
#define VG_PACKAGE_API
#endif
#endif



