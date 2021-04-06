#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory.h>
#include "PTSDLog.h"

namespace PTSD
{
	
	class LogImpl
	{
		LogImpl() = default;

		std::vector<std::shared_ptr<spdlog::logger>> mLoggers;//0 for engine, 1 for client
		spdlog::sink_ptr mConsoleSink;
		static LogImpl* mInstance;
		spdlog::level::level_enum spdLevel(PTSD::LogLevel level);
		spdlog::level::level_enum mDefaultLevel;
	public:
		~LogImpl() = default;

		static LogImpl* getInstance()
		{
			if (!mInstance)
				mInstance = new LogImpl();
			return mInstance;
		}

		void init(LogLevel lvl);

		std::shared_ptr<spdlog::logger> getLogger(size_t n);
		size_t createLogger(const std::string& name, bool separateLog = false);
	};
}