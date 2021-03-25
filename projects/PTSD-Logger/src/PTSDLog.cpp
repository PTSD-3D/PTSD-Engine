#include <iostream>
#include "PTSDLog.h"
#include "LogImpl.h"
#include "spdlog\spdlog.h"

namespace PTSD {

	/**
	 * \brief filters out messages under level param
	 * \param level filter 
	 */
	void Log::setLogLevel(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Trace:
			spdlog::set_level(spdlog::level::trace);
			break;
		case LogLevel::Info:
			spdlog::set_level(spdlog::level::info);
			break;
		case LogLevel::Warning:
			spdlog::set_level(spdlog::level::warn);
			break;
		case LogLevel::Error:
			spdlog::set_level(spdlog::level::err);
			break;
		case LogLevel::Critical:
			spdlog::set_level(spdlog::level::critical);
			break;
		case LogLevel::NONE:
			spdlog::set_level(spdlog::level::off);
			break;
		}
	}

	size_t Log::createLogger(const char* name, bool individualFile)
	{
		return LogImpl::getInstance()->createLogger(name, individualFile);
	}

	void LOG(const char* msg, LogLevel lv, size_t logId)
	{
		std::shared_ptr<spdlog::logger> lg = LogImpl::getInstance()->getLogger(logId);
		switch (lv)
		{
		case Trace:
			lg->trace(msg);
			break;
		case Info:
			lg->info(msg);
			break;
		case Warning:
			lg->warn(msg);
			break;
		case Error:
			lg->error(msg);
			break;
		case Critical:
			lg->critical(msg);
			break;
		default:
			break;
		}
	}

	/**
	 * \brief Initializes logging subsystem
	 * \param level filters lower than level messages
	 * \return 
	 */
	int Log::Init(LogLevel level){
		LogImpl::getInstance()->Init();
		setLogLevel(level);
		return 0;
	}

	int Log::Shutdown()
	{
		delete LogImpl::getInstance();
		return 0;
	}
}
