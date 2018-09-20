#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include <boost/log/trivial.hpp>

namespace easy_engine {
	namespace logger {
		class Logger {
			public:
				Logger(const char* prefix);
				void debug(std::string message);
				void info(std::string message);
				void warning(std::string message);
				void error(std::string message);
				void fatal(std::string message);
			private:
				const char* prefix;
		};
	}
} 
#endif // !LOGGER_H
