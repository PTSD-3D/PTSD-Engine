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
		(*state).open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::os, sol::lib::table);

		(*state).require_file("reqNamespace", "./assets/scripts/engine/namespace.lua");
		(*state).require_file("reqMiddleclass", "./assets/scripts/engine/middleclass.lua");
		(*state).require_file("reqComponent", "./assets/scripts/engine/Component.lua");
		(*state).require_file("reqEntity", "./assets/scripts/engine/Entity.lua");
		(*state).require_file("reqSystem", "./assets/scripts/engine/System.lua");
		(*state).require_file("reqEntityManager", "./assets/scripts/engine/EntityManager.lua");
		(*state).require_file("reqEngine", "./assets/scripts/engine/initEngine.lua");

		(*state).script_file("./assets/scripts/engine/test.lua"); //Test file of engine initialization, any other code goes below...

		//Binding of external functions
		if (bindGraphicsComponents() &&
			bindPhysicsComponents() &&
			bindUIComponents() &&
			bindSoundComponents() &&
			bindInputComponents() &&
			bindGenericComponents()) {
		}

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

	Entity* ScriptManager::createEntity()
	{
		PTSD::Entity* ent = entityManager->createEntity();
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

	bool ScriptManager::bindGraphicsComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Graphics Components... @ScriptManager, BindGraphicsComponents()");

		(*state).set_function("translate", &PTSD::Camera::translate, PTSD::Graphics::getInstance()->getCam());
		(*state).set_function("getWindowWidth", &PTSD::Graphics::getWindowWidth, PTSD::Graphics::getInstance());
		(*state).set_function("getWindowHeight", &PTSD::Graphics::getWindowHeight, PTSD::Graphics::getInstance());
		(*state).set_function("rotateCamera", &PTSD::Camera::mouseRotate, PTSD::Graphics::getInstance()->getCam());

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
		(*state).set_function("getMouseRelativePosition", &PTSD::Input::getMouseRelativePosition, PTSD::Input::getInstance());
		(*state).set_function("resetMouse", &PTSD::Input::cleanMouseDelta, PTSD::Input::getInstance());

		//This should be expanded or reconsidered in the future.
		(*state).new_enum<Scancode>("PTSDKeys", {
			{"W", Scancode::SCANCODE_W},
			{"A", Scancode::SCANCODE_A},
			{"S", Scancode::SCANCODE_S},
			{"D", Scancode::SCANCODE_D},
			{"Shift", Scancode::SCANCODE_LSHIFT}
			});

		return true;
	}
	bool ScriptManager::bindGenericComponents()
	{
		//Init everything
		PTSD::LOG("Binding Generic Components... @ScriptManager, BindGenericComponents()");

		(*state).new_usertype<Vec3Placeholder>("vec3", sol::constructors<Vec3Placeholder(double, double, double)>(), "x", &Vec3Placeholder::x, "y", &Vec3Placeholder::y, "z", &Vec3Placeholder::z);
		(*state).new_usertype<Vector2D>("vec2", sol::constructors<Vector2D(double, double)>(), "x", &Vector2D::x, "y", &Vector2D::y, sol::meta_function::subtraction, &Vector2D::operator-,
			sol::meta_function::addition, &Vector2D::operator+, sol::meta_function::multiplication, &Vector2D::operator*);

		return true;
	}
}