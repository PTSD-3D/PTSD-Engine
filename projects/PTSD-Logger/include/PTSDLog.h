#pragma once
#if defined(_MSC_VER)
	#ifdef _PTSDLOG
		#define LOGAPI  __declspec(dllexport)   // export DLL information
	#else
		#define LOGAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDLOG
		#define LOGAPI __attribute__((visibility("default")))
	#else
		#define LOGAPI
	#endif 
#endif 


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
	class LOGAPI Log {
	public:
		int Init(LogLevel level);
		//this system has no update
		int Shutdown();
		~Log() = default;
		Log() {}

		void setLogLevel(LogLevel level);

		size_t createLogger(const char* name, bool individualFile = false);
	};


	LOGAPI void LOG(const char* msg, LogLevel lv = LogLevel::Info, size_t logId = 0);


}