#include <Logger.h>

namespace easy_engine {
	namespace logger {

		Logger::Logger(const char* prefix) {
			this->prefix = prefix;
		}

		void Logger::debug(std::string message) {
			BOOST_LOG_TRIVIAL(debug) << "[" << this->prefix <<  "] " << message;
		}

		void Logger::info(std::string message) {
			BOOST_LOG_TRIVIAL(info) << "[" << this->prefix << "] " << message;
		}

		void Logger::warning(std::string message) {
			BOOST_LOG_TRIVIAL(warning) << "[" << this->prefix << "] " << message;
		}

		void Logger::error(std::string message) {
			BOOST_LOG_TRIVIAL(error) << "[" << this->prefix << "] " << message;
		}

		void Logger::fatal(std::string message) {
			BOOST_LOG_TRIVIAL(fatal) << "[" << this->prefix << "] " << message;
		}
	}
}