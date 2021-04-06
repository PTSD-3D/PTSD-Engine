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
		state.open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::os, sol::lib::table);

		state.require_file("reqNamespace", "./assets/scripts/engine/namespace.lua");
		state.require_file("reqMiddleclass", "./assets/scripts/engine/middleclass.lua");
		state.require_file("reqComponent", "./assets/scripts/engine/Component.lua");
		state.require_file("reqEntity", "./assets/scripts/engine/Entity.lua");
		state.require_file("reqEntityManager", "./assets/scripts/engine/EntityManager.lua");
		state.require_file("reqEngine", "./assets/scripts/engine/initEngine.lua");

		state.script(R"(
local eng = reqEngine

reqEngine.initialize({globals = true});

local Position = eng.Component.create("position", {"x", "y"}, {x = 0, y = 0})

print(Position(150,25).x)

local player = eng.Entity:new()
player:initialize()

player:add(Position(30, 25))
local test = player:get("position")
print(test.x)
)");
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
		state["Update"]();
		return state["Exit"];
	}

	void ScriptingImplementation::shutdown()
	{
		//Clean entity internal representation (?)

	}

	void ScriptingImplementation::addEntity(void* entityPtr)
	{
		//Creates an entity in Lua and relates it to this pointer
		//Entity["Start"]();
	}

	void ScriptingImplementation::deleteEntity(size_t entityID)
	{
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