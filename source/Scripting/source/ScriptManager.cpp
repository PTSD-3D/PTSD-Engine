#include "ScriptManager.h"
#include <sol/sol.hpp>
#include "lua.hpp"
#include "ECS.h"
#include "EntityManager.h"

/*
Include every PTSD-System to expose its public API to our Scripting state
*/
#include "PTSDInput.h"
#include "PTSDGraphics.h"
#include "Camera.h"
#include "PTSDUI.h"
#include "PTSDPhysics.h"
#include "PTSDVectors.h"
#include "PTSDLog.h"

namespace PTSD {
	/**
	 * \brief Creates the objects for lua state and entityManager
	 */
	ScriptManager::ScriptManager() : state(new sol::state()), entityManager(new EntityManager())
	{}

	/*
	 * \brief Frees up allocated memory
	 */
	ScriptManager::~ScriptManager() {
		delete entityManager;
		delete state;
	}

	void ScriptManager::run(const std::string& scriptFile)
	{
		std::string mssg = scriptFile + " loading... @PTSDScripting, Run()";
		PTSD::LOG(mssg.c_str(), PTSD::Info);

		(*state).do_file("./assets/scripts/" + scriptFile);
	}


	/**
	 * \brief Binds external functions to lua state and initializes main lua engine.
	 * \return true if everything went OK.
	 */
	bool ScriptManager::init() {
		//Lua state initialization
		(*state).open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::os, sol::lib::table, sol::lib::debug);

		(*state).require_file("reqNamespace", "./assets/scripts/Engine/namespace.lua");
		(*state).require_file("reqMiddleclass", "./assets/scripts/Engine/middleclass.lua");
		(*state).require_file("reqComponent", "./assets/scripts/Engine/Component.lua");
		(*state).require_file("reqEntity", "./assets/scripts/Engine/Entity.lua");
		(*state).require_file("reqSystem", "./assets/scripts/Engine/System.lua");
		(*state).require_file("reqEntityManager", "./assets/scripts/Engine/EntityManager.lua");
		(*state).require_file("reqEngine", "./assets/scripts/Engine/initEngine.lua");
		(*state).require_file("sampleScene", "./assets/scripts/Client/sampleScene.lua");
		(*state).script_file("./assets/scripts/Engine/EntityLoader.lua");

		//Binding of external functions
		if (bindLoggerComponents() &&
			bindGraphicsComponents() &&
			bindPhysicsComponents() &&
			bindUIComponents() &&
			bindSoundComponents() &&
			bindInputComponents() &&
			bindScriptingComponents() &&
			bindGenericComponents()) {
		}

		(*state).script_file("./assets/scripts/Engine/test.lua"); //Test file of engine initialization, any other code goes below...

		return true;
	}

	bool ScriptManager::update()
	{
		entityManager->update();
		//state.script("manager:update(1)");
		(*state)["manager"]["update"]((*state)["manager"], 1); //This and line above are both valid
		(*state)["Update"]();
		//TODO exit state
		return true;
		//return state["Exit"];
	}

	void ScriptManager::shutdown()
	{
		//Clean entity internal representation (?)
	}

	std::shared_ptr<Entity> ScriptManager::createEntity(UUID entityID)
	{
		auto ent = entityManager->createEntity(entityID);
		//Creates an entity in Lua and relates it to this pointer
		//Entity["Start"]();

		return ent;
	}

	void ScriptManager::deleteEntity(UUID entityID)
	{
		entityManager->deleteEntity(entityID);
		//Deletes entity in Lua
		//Entity["Delete"]();
	}

	bool ScriptManager::bindLoggerComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Logger Components... @ScriptManager, BindLoggerComponents()");

		(*state).new_enum("LogLevel",
			"Trace", LogLevel::Trace,
			"Info", LogLevel::Info,
			"Warning", LogLevel::Warning,
			"Error", LogLevel::Error,
			"Critical", LogLevel::Critical,
			"NONE", LogLevel::NONE);

		(*state).set_function("LOG", sol::overload(&PTSD::LOG, &PTSD::LOGInfoMsg));

		return true;
	}

	bool ScriptManager::bindGraphicsComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Graphics Components... @ScriptManager, BindGraphicsComponents()");

		(*state).set_function("translate", &PTSD::Camera::translate, PTSD::Graphics::getInstance()->getCam());

		return true;
	}
	bool ScriptManager::bindPhysicsComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Physics Components... @ScriptManager, BindPhysicsComponents()");
		return true;
	}
	bool ScriptManager::bindSoundComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Sound Components... @ScriptManager, BindSoundComponents()");
		return true;
	}
	bool ScriptManager::bindUIComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA UI Components... @ScriptManager, BindUIComponents()");
		return true;
	}
	bool ScriptManager::bindInputComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Input Components... @ScriptManager, BindInputComponents()");

		(*state).set_function("keyPressed", &PTSD::Input::keyPressed, PTSD::Input::getInstance());

		//This should be expanded or reconsidered in the future.
		(*state).new_enum<Scancode>("PTSDKeys", {
			{"W", Scancode::SCANCODE_W},
			{"A", Scancode::SCANCODE_A},
			{"S", Scancode::SCANCODE_S},
			{"D", Scancode::SCANCODE_D}
			});

		return true;
	}
	bool ScriptManager::bindScriptingComponents() {
		(*state).set_function("PTSDCreateEntity", &PTSD::ScriptManager::createEntity, this);

		return true;
	}
	bool ScriptManager::bindGenericComponents()
	{
		//Init everything
		PTSD::LOG("Binding Generic Components... @ScriptManager, BindGenericComponents()");

		(*state).new_usertype<Vec3Placeholder>("vec3", sol::constructors<Vec3Placeholder(float, float, float)>());

		return true;
	}
}