#pragma once

namespace PTSD {
	class ScriptingImplementation;
	class Scripting {
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