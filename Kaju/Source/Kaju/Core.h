#pragma once

#ifdef KJ_PLATFORM_WINDOWS
	#ifdef KJ_BUILD_DLL
		#define KAJU_API __declspec(dllexport)
	#else
		#define KAJU_API __declspec(dllimport)
	#endif // KJ_BUILD_DLL
#else
	#error Kaju Only Supports Windows!
#endif // KJ_PLATFORM_WINDOWS

#ifdef KJ_ENABLE_ASSERTS
	#define KJ_ASSERT(x, ...) {if(!(x)){KJ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define KJ_CORE_ASSERT(x, ...) {if(!(x)){KJ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define KJ_ASSERT(x, ...)
	#define KJ_CORE_ASSERT(x, ...)
#endif // KJ_ENABLE_ASSERTS
