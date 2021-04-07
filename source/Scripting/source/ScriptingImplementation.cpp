#include "ScriptingImplementation.h"

/*
Include every PTSD-System to expose its public API to our Scripting state
*/
#include "PTSDInput.h"
#include "PTSDGraphics.h"
#include "Camera.h"
//#include "PTSDUI.h"
//#include "PTSDPhysics.h"
#include "PTSDScripting.h"
#include "PTSDVectors.h"
#include "PTSDLog.h"

namespace PTSD {
	ScriptingImplementation::ScriptingImplementation() {
		state.open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::os, sol::lib::table);

		state.require_file("reqNamespace", "./assets/scripts/engine/namespace.lua");
		state.require_file("reqMiddleclass", "./assets/scripts/engine/middleclass.lua");
		state.require_file("reqComponent", "./assets/scripts/engine/Component.lua");
		state.require_file("reqEntity", "./assets/scripts/engine/Entity.lua");
		state.require_file("reqSystem", "./assets/scripts/engine/System.lua");
		state.require_file("reqEntityManager", "./assets/scripts/engine/EntityManager.lua");
		state.require_file("reqEngine", "./assets/scripts/engine/initEngine.lua");

		state.script_file("./assets/scripts/engine/test.lua"); //Test file of engine initialization, any other code goes below...
	}

	void ScriptingImplementation::run(std::string scriptFile)
	{
		std::string mssg = scriptFile + " loading... @PTSDScripting, Run()";
		PTSD::LOG(mssg.c_str(), PTSD::Info);

		state.do_file("./assets/scripts/" + scriptFile);
	}

	
	
	/**
	 * \brief Inicializa todos los componentes y funciones(API) de todos los sistemas. Devuelve true si todo ha ido bien.
	 * \return false si alguna inicializaci�n de componentes o  funciones falla.
	 */
	bool ScriptingImplementation::init() {
		if (bindGraphicsComponents() &&
			bindPhysicsComponents() &&
			bindUIComponents() &&
			bindSoundComponents() &&
			bindInputComponents() &&
			bindGenericComponents()) {
		}

		return true;
	}

	bool ScriptingImplementation::update()
	{
		//state.script("manager:update(1)");
		state["manager"]["update"](state["manager"],1); //This and line above are both valid
		entityManager_.update();
		state["Update"]();
		//TODO exit state
		return true;
		//return state["Exit"];
	}

	void ScriptingImplementation::shutdown()
	{
		//Clean entity internal representation (?)

	}

	Entity* ScriptingImplementation::createEntity()
	{
		PTSD::Entity* ent = entityManager_.createEntity();
		//Creates an entity in Lua and relates it to this pointer
		//Entity["Start"]();

		return ent;
	}

	void ScriptingImplementation::deleteEntity(UUID entityID)
	{
		entityManager_.deleteEntity(entityID);
		//Deletes entity in Lua
		//Entity["Delete"]();
	}

	bool ScriptingImplementation::bindGraphicsComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Graphics Components... @ScriptingImplementation, BindGraphicsComponents()");

		state.set_function("translate", &PTSD::Camera::translate , PTSD::Graphics::getInstance()->getCam());

		return true;
	}
	bool ScriptingImplementation::bindPhysicsComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Physics Components... @ScriptingImplementation, BindPhysicsComponents()");
		return true;
	}
	bool ScriptingImplementation::bindSoundComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Sound Components... @ScriptingImplementation, BindSoundComponents()");
		return true;
	}
	bool ScriptingImplementation::bindUIComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA UI Components... @ScriptingImplementation, BindUIComponents()");
		return true;
	}
	bool ScriptingImplementation::bindInputComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Input Components... @ScriptingImplementation, BindInputComponents()");

		state.set_function("keyPressed", &PTSD::Input::keyPressed, PTSD::Input::getInstance());

		//This should be expanded or reconsidered in the future.
		state.new_enum<Scancode>("PTSDKeys", {
			{"W", Scancode::SCANCODE_W},
			{"A", Scancode::SCANCODE_A},
			{"S", Scancode::SCANCODE_S},
			{"D", Scancode::SCANCODE_D}
		});

		return true;
	}
	bool ScriptingImplementation::bindGenericComponents()
	{
		//Init everything
		PTSD::LOG("Binding Generic Components... @ScriptingImplementation, BindGenericComponents()");

		state.new_usertype<Vec3Placeholder>("vec3", sol::constructors<Vec3Placeholder(float, float, float)>());

		return true;
	}
}