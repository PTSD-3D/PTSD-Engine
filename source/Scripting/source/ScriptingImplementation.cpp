#include "ScriptingImplementation.h"

/*
Include every PTSD-System to expose its public API to our Scripting state
*/
#include "PTSDInput.h"
#include "PTSDGraphics.h"
#include "Camera.h"
//#include "PTSDUI.h"
//#include "PTSDPhysics.h"
#include "PTSDScripting.h" //debería ser el ECS
#include "PTSDVectors.h"
#include "PTSDLog.h"

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
			bindSoundComponents() &&
			bindInputComponents() &&
			bindGenericComponents()) {
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