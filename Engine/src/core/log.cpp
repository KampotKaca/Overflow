#include "pch.h"
#include "log.h"

namespace overflow
{
	std::shared_ptr<spdlog::logger> log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> log::s_ClientLogger;

	void log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("[Overflow]");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("[Client]");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}