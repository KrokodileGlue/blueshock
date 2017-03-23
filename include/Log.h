#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>

enum class LogLevel {
	ERROR, WARNING, INFO, DEBUG1, DEBUG2, DEBUG3
};

std::ostringstream& log(LogLevel level);
void dump_log();

#endif
