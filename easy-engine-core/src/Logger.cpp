#include <EasyEngine/eepch.h>
#include <EasyEngine/Logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace easy_engine {
	namespace logger {

		std::shared_ptr<spdlog::logger> Logger::s_CoreLogger_;
		std::shared_ptr<spdlog::logger> Logger::s_ClientLogger_;

		void Logger::Init() {
			spdlog::set_pattern("%^[%T] %n [thread %t]: %v%$");
			s_CoreLogger_ = spdlog::stdout_color_mt("EasyEngine Core");
			s_CoreLogger_->set_level(spdlog::level::trace);

			s_ClientLogger_ = spdlog::stdout_color_mt("EasyEngine Application");
			s_ClientLogger_->set_level(spdlog::level::trace);
		}
	}
}