#pragma once

// 1.Standard headers
#include <memory>

// 2.Third party headers
#include <spdlog/spdlog.h>

// 3.Project specific headers
#include "Core.h"

namespace KJ
{
	class Log
	{
	public:
		KAJU_API static void Init();

		KAJU_API inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		KAJU_API inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

// Core log macros
#define KJ_CORE_TRACE(...)    ::KJ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KJ_CORE_INFO(...)     ::KJ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KJ_CORE_WARN(...)     ::KJ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KJ_CORE_ERROR(...)    ::KJ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KJ_CORE_FATAL(...)    ::KJ::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define KJ_TRACE(...)         ::KJ::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KJ_INFO(...)          ::KJ::Log::GetClientLogger()->info(__VA_ARGS__)
#define KJ_WARN(...)          ::KJ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KJ_ERROR(...)         ::KJ::Log::GetClientLogger()->error(__VA_ARGS__)
#define KJ_FATAL(...)         ::KJ::Log::GetClientLogger()->fatal(__VA_ARGS__)