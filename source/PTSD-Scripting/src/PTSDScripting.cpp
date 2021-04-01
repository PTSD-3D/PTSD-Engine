#include <iostream>
#include "PTSDScripting.h"
#include "ScriptingImplementation.h"
#include "lua.hpp"
#include <sol/sol.hpp>


namespace PTSD {
	int Scripting::init() {
		std::cout << "Initializing lua scripting system\n";
		
		sol::state luaState;
		luaState.open_libraries(sol::lib::base);

		mScriptMgr = new ScriptingImplementation();
		if (!mScriptMgr->init()) {
			printf("F");
		}
		else {
			luaState.script("print('Lua initialized correctly and working!')");
		}

		return 0;
	}

	Scripting::~Scripting() {
		if (mScriptMgr != nullptr)
			delete mScriptMgr;
	}

	void Scripting::run(std::string script)
	{
		mScriptMgr->run(script);
	}

	bool Scripting::update()
	{
		return mScriptMgr->update();
	}

	void Scripting::shutdown()
	{
		mScriptMgr->shutdown();
	}

	void Scripting::addEntity(void* entityPtr)
	{
		mScriptMgr->addEntity(entityPtr);
	}

	void Scripting::deleteEntity(size_t entityID)
	{
		mScriptMgr->deleteEntity(entityID);
	}
}