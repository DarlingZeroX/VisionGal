#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#ifdef CORE_MODULE_EXPORT
#define CORE_MODULE_API __declspec(dllexport)
#else
#define CORE_MODULE_API __declspec(dllimport)
#endif
#endif