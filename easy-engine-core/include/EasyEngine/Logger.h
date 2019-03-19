#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace easy_engine {
	namespace logger {
		class EASY_ENGINE_API Logger {
			public:
				static void Init();

				inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger_; }
				inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger_; }
			private:
				static std::shared_ptr<spdlog::logger> s_CoreLogger_;
				static std::shared_ptr<spdlog::logger> s_ClientLogger_;
		};
	}
}

// Core log macros
#define EE_CORE_TRACE(...)      ::easy_engine::logger::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define EE_CORE_INFO(...)       ::easy_engine::logger::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define EE_CORE_WARN(...)       ::easy_engine::logger::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define EE_CORE_ERROR(...)      ::easy_engine::logger::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define EE_CORE_CRITICAL(...)   ::easy_engine::logger::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EE_TRACE(...)			::easy_engine::logger::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define EE_INFO(...)			::easy_engine::logger::Logger::GetClientLogger()->info(__VA_ARGS__)
#define EE_WARN(...)			::easy_engine::logger::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define EE_ERROR(...)			::easy_engine::logger::Logger::GetClientLogger()->error(__VA_ARGS__)
#define EE_CRITICAL(...)		::easy_engine::logger::Logger::GetClientLogger()->critical(__VA_ARGS__)

#endif // !LOGGER_H
