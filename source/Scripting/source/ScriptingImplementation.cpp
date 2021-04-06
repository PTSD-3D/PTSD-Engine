#include "ScriptingImplementation.h"

/*
Include every PTSD-System to expose its public API to our Scripting state
*/
#include "PTSDInput.h"
#include "PTSDGraphics.h"
//#include "PTSDUI.h"
//#include "PTSDPhysics.h"
#include "PTSDScripting.h" //debería ser el ECS

namespace PTSD {
	ScriptingImplementation::ScriptingImplementation() {
		state.open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::os);
	}

	void ScriptingImplementation::run(std::string scriptFile)
	{
		state.do_file("./assets/scripts/" + scriptFile);
	}

	
	
	/**
	 * \brief Inicializa todos los componentes y funciones(API) de todos los sistemas. Devuelve true si todo ha ido bien.
	 * \return false si alguna inicialización de componentes o  funciones falla.
	 */
	bool ScriptingImplementation::init() {
		if (bindGraphicsComponents() &&
			bindPhysicsComponents() &&
			bindUIComponents() &&
			bindSoundComponents()) {
			//state.do_file("./assets/PTSDComponents.lua");
			//state.do_file("./assets/UserComponent.lua");
			// state["Start"]();
			// while(!state["Exit"])
			// 	state["Update"]();
		}

		return true;
	}

	bool ScriptingImplementation::update()
	{
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
		return true;
	}
	bool ScriptingImplementation::bindPhysicsComponents()
	{
		//Init everything
		return true;
	}
	bool ScriptingImplementation::bindSoundComponents()
	{
		//Init everything
		return true;
	}
	bool ScriptingImplementation::bindUIComponents()
	{
		//Init everything
		return true;
	}
}