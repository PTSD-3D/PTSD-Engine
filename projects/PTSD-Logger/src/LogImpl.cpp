#include  "LogImpl.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace PTSD
{
	LogImpl* LogImpl::m_instance = nullptr;

	spdlog::level::level_enum LogImpl::spdLevel(PTSD::LogLevel level)
	{
		switch (level)
		{
		case Trace:
			return spdlog::level::trace;
		case Info:
			return spdlog::level::info;
		case Warning:
			return spdlog::level::warn;
		case Error:
			return spdlog::level::err;
		case Critical:
			return spdlog::level::critical;
		default:
			return spdlog::level::off;
		}
	}

	void LogImpl::Init(LogLevel lvl)
	{
		m_consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		m_defaultLevel = spdLevel(lvl);
		createLogger("Engine", true);
		createLogger("Client", true);
	}

	std::shared_ptr<spdlog::logger> LogImpl::getLogger(size_t n)
	{
		if (n > m_loggers.size()) {
			m_loggers[0]->error("Logger not found");
			return nullptr;
		}
		return m_loggers[n];
	}

	/**
	 * \brief creates a new Logger
	 * \param name name of the logger
	 * \param separateLog set to true to store this logger output on a separate file
	 * \return logger ID
	 */
	size_t LogImpl::createLogger(const std::string& name, bool separateLog)
	{
		std::vector<spdlog::sink_ptr> sinkVec;
		sinkVec.push_back(m_consoleSink);
		if (separateLog)
			sinkVec.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("logs/" + name + ".log"));

		m_loggers.push_back(std::make_shared<spdlog::logger>(name, sinkVec.begin(), sinkVec.end()));
		m_loggers.back()->set_pattern("%^[%T] %n: %v%$");
		m_loggers.back()->set_level(m_defaultLevel);
		return m_loggers.size() - 1;
	}
}