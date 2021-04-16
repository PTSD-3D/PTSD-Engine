#include <iostream>
#include "LogManager.h"
#include "LogImpl.h"
#include "spdlog/spdlog.h"

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

	/**
	 * \brief Creates a new logger WARNING store the id carefully
	 * \param name of the logger and possible file
	 * \param individualFile true to store output separately
	 * \return id of the logger
	 */
	size_t Log::createLogger(const char* name, bool individualFile)
	{
		return LogImpl::getInstance()->createLogger(name, individualFile);
	}

	/**
	 * \brief Prints a debug message
	 * \param msg message to print
	 * \param lv importance of the message
	 * \param logId Engine=0, Client=1, Extra >1
	 */
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
	 * \return 0 on correct
	 */
	int Log::init(LogLevel level) {
		setLogLevel(level);
		LogImpl::getInstance()->init(level);
		return 0;
	}
	/**
	 * \brief Deletes the private implementation singleton
	 * \return 0 on correct
	 */
	int Log::shutdown()
	{
		delete LogImpl::getInstance();
		return 0;
	}
}
