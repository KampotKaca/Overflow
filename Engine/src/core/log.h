#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace overflow
{
	class log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& Core() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& Client() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

#define CORE_TRACE(...) ::overflow::log::Core()->trace(__VA_ARGS__)
#define CORE_INFO(...)  ::overflow::log::Core()->info(__VA_ARGS__)
#define CORE_WARN(...)  ::overflow::log::Core()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::overflow::log::Core()->error(__VA_ARGS__)

#define LOG_TRACE(...)      ::overflow::log::Client()->trace(__VA_ARGS__)
#define LOG_INFO(...)       ::overflow::log::Client()->info(__VA_ARGS__)
#define LOG_WARN(...)       ::overflow::log::Client()->warn(__VA_ARGS__)
#define LOG_ERROR(...)      ::overflow::log::Client()->error(__VA_ARGS__)
}

#endif //LOG_H