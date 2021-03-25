#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory.h>
#include "PTSDLog.h"

namespace PTSD
{
	
	class LogImpl
	{
		std::vector<std::shared_ptr<spdlog::logger>> m_loggers;//0 for engine, 1 for client
		spdlog::sink_ptr m_consoleSink;
		static LogImpl* m_instance;
		LogImpl() = default;
		spdlog::level::level_enum spdLevel(PTSD::LogLevel level);
		spdlog::level::level_enum m_defaultLevel;
	public:
		static LogImpl* getInstance()
		{
			if (!m_instance)
				m_instance = new LogImpl();
			return m_instance;
		}
		void Init(LogLevel lvl);
		std::shared_ptr<spdlog::logger> getLogger(size_t n);
		size_t createLogger(const std::string& name, bool separateLog = false);
		~LogImpl() = default;
	};
}