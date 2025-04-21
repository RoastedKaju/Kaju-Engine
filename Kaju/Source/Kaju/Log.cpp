#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> KJ::Log::s_coreLogger;
std::shared_ptr<spdlog::logger> KJ::Log::s_clientLogger;

void KJ::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_coreLogger = spdlog::stdout_color_mt("KAJU");
	s_coreLogger->set_level(spdlog::level::trace);

	s_clientLogger = spdlog::stdout_color_mt("APP");
	s_clientLogger->set_level(spdlog::level::trace);
}
