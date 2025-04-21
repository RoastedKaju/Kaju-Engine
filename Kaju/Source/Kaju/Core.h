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
