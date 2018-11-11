#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/msvc_sink.h>

void InitLog()
{
	spdlog::set_async_mode(8192);

	std::vector<spdlog::sink_ptr> Sinks;
	Sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
	Sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
	Sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_mt>("log.log"));

	auto combined_logger = std::make_shared<spdlog::logger>("log", begin(Sinks), end(Sinks));
	spdlog::register_logger(combined_logger);
	spdlog::get("log")->flush_on(spdlog::level::err);
}

template <typename Arg1, typename... Args>
void LogInfo(const char* fmt, const Arg1 &arg1, const Args&... args)
{
	spdlog::get("log")->info(fmt, arg1, args...);
}

template<typename T>
void LogInfo(const T& msg)
{
	spdlog::get("log")->info(msg);
}