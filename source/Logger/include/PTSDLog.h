#pragma once

#include <string>
#include <memory>

namespace PTSD {
	enum LogLevel
	{
		Trace = 0,
		Info,
		Warning,
		Error,
		Critical,
		NONE, // really, really not recommended
	};
	class LogImpl;
	class Log {
	public:
		~Log() = default;
		Log() {}

		int init(LogLevel level);
		//this system has no update
		int shutdown();

		void setLogLevel(LogLevel level);

		size_t createLogger(const char* name, bool individualFile = false);
	};


	void LOG(const char* msg, LogLevel lv = LogLevel::Info, size_t logId = 0);
	void LOGInfoMsg(const char* msg);
}