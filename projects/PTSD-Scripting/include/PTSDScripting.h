#pragma once

#if defined(_MSC_VER)
	#ifdef _PTSDSCRIPTING
		#define SCRIPTINGAPI  __declspec(dllexport)   // export DLL information
	#else
		#define SCRIPTINGAPI  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#ifdef _PTSDSCRIPTING
		#define SCRIPTINGAPI __attribute__((visibility("default")))
	#else
		#define SCRIPTINGAPI
	#endif 
#endif 

namespace PTSD {
	class ScriptingImplementation;
	class SCRIPTINGAPI Scripting {
	private:
		ScriptingImplementation* mScriptMgr;
	public:
		Scripting() : mScriptMgr(nullptr) {};
		~Scripting();

		int init();
		void run(std::string script);
		bool update();
		void shutdown();

		void addEntity(void* entityPtr);
		void deleteEntity(size_t entityID);
	};
}