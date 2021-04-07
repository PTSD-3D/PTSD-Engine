#pragma once
#include "ECS.h"

namespace PTSD {
	class ScriptingImplementation;
	class Entity;
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

		Entity* createEntity();
		void deleteEntity(UUID entityID);
	};
}
