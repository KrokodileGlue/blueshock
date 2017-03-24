#include "engine/Log.h"

#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>

std::ostringstream oss;
std::ostringstream null_stream;

LogLevel max_log_level = LogLevel::DEBUG3;

std::ostringstream& log(LogLevel level)
{
	if (level > max_log_level) {
		null_stream.str(""), null_stream.clear();
		return null_stream;
	}

	oss << std::endl;

	std::chrono::time_point<std::chrono::system_clock> time;
	time = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(time);

	std::string time_str = std::ctime(&end_time);
	time_str.erase(std::remove(time_str.begin(), time_str.end(), '\n'), time_str.end());
	oss << time_str;

	switch (level) {
	case LogLevel::ERROR: oss << " [ERROR] "; break;
	case LogLevel::WARNING: oss << " [WARNING] "; break;
	case LogLevel::INFO: oss << " [INFO] "; break;
	case LogLevel::DEBUG1:
	case LogLevel::DEBUG2:
	case LogLevel::DEBUG3: oss << " [DEBUG] "; break;
	}

	return oss;
}

void dump_log()
{
	std::ofstream out("blueshock.log");
	out << oss.str();
	out.close();
}
