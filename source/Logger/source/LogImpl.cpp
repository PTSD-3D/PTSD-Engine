#include  "LogImpl.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace PTSD
{
	LogImpl* LogImpl::mInstance = nullptr;

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

	void LogImpl::init(LogLevel lvl)
	{
		mConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		mDefaultLevel = spdLevel(lvl);
		createLogger("Engine", true);
		createLogger("Client", true);
	}

	std::shared_ptr<spdlog::logger> LogImpl::getLogger(size_t n)
	{
		if (n > mLoggers.size()) {
			mLoggers[0]->error("Logger not found");
			return nullptr;
		}
		return mLoggers[n];
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
		sinkVec.push_back(mConsoleSink);
		if (separateLog)
			sinkVec.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("logs/" + name + ".log"));

		mLoggers.push_back(std::make_shared<spdlog::logger>(name, sinkVec.begin(), sinkVec.end()));
		mLoggers.back()->set_pattern("%^[%T] %n: %v%$");
		mLoggers.back()->set_level(mDefaultLevel);
		return mLoggers.size() - 1;
	}
	void LogImpl::shutdown(){
		if (mInstance)
		{
			mInstance = nullptr;
			mLoggers.clear();
		}
	}
}
