#include "ScriptManager.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "lua.hpp"
#include "ECS.h"
#include "EntityManager.h"
#include <string>
#include <iostream>
#include <filesystem>
/*
Include every PTSD-System to expose its public API to our Scripting state
*/
#include "InputManager.h"
#include "GraphicsManager.h"
#include "SoundManager.h"
#include "Camera.h"
#include "UIManager.h"
#include "PhysicsManager.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "PTSDVectors.h"
#include "LogManager.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "PTSDVectors.h"

namespace fs = std::filesystem;
namespace PTSD {
	/**
	 * \brief Creates the objects for lua state and entityManager
	 */
	ScriptManager::ScriptManager() : state(new sol::state()), entityManager(new EntityManager()) {}

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
		(*state).open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::os, sol::lib::table, sol::lib::debug, sol::lib::package, sol::lib::string);

		(*state).require_file("reqNamespace", "./assets/scripts/Engine/namespace.lua");
		(*state).require_file("reqMiddleclass", "./assets/scripts/Engine/middleclass.lua");

		//Engine components
		(*state).require_file("reqComponent", "./assets/scripts/Engine/Component.lua");
		(*state).require_file("reqEntity", "./assets/scripts/Engine/Entity.lua");
		(*state).require_file("reqSystem", "./assets/scripts/Engine/System.lua");
		//Events
		(*state).require_file("reqComponentAddedEvent", "./assets/scripts/Engine/Events/ComponentAdded.lua");
		(*state).require_file("reqComponentRemovedEvent", "./assets/scripts/Engine/Events/ComponentRemoved.lua");
		(*state).require_file("reqCollisionEvent", "./assets/scripts/Engine/Events/Collision.lua");
		(*state).require_file("reqEventManager", "./assets/scripts/Engine/EventManager.lua");
		(*state).require_file("reqEntityManager", "./assets/scripts/Engine/EntityManager.lua");
		(*state).require_file("reqEngine", "./assets/scripts/Engine/initEngine.lua");
		(*state).require_file("reqPrefab", "./assets/scripts/Engine/Prefab.lua");
		(*state).require_file("reqSceneConfigurations", "./assets/scripts/Engine/Prefab.lua");
		for (const auto& entry : fs::directory_iterator("./assets/scripts/Client/Prefabs"))
		{
			(*state).script_file(entry.path().string());
		}

		//(*state).require_file("sampleScene", "./assets/scripts/Client/sampleScene.lua");
		(*state).script_file("./assets/scripts/Engine/EntityLoader.lua");

		//Binding of external functions
		if (bindGenericComponents() &&
			bindLoggerComponents() &&
			bindGraphicsComponents() &&
			bindPhysicsComponents() &&
			bindUIComponents() &&
			bindSoundComponents() &&
			bindInputComponents() &&
			bindScriptingComponents()) {
		}

		//Resources
		(*state).script_file("./assets/scripts/Client/resources.lua");
		(*state).script_file("./assets/scripts/Engine/resourceLoader.lua");

		//Prefabs and Scenes
		(*state).require_file("reqEventManager", "./assets/scripts/Engine/EventManager.lua");
		(*state).require_file("reqEntityManager", "./assets/scripts/Engine/EntityManager.lua");
		(*state).require_file("reqEngine", "./assets/scripts/Engine/initEngine.lua");
		(*state).require_file("reqPrefab", "./assets/scripts/Engine/Prefab.lua");
		for (const auto& entry : fs::directory_iterator("./assets/scripts/Client/Prefabs"))
		{
			(*state).script_file(entry.path().string());
		}
		(*state).script_file("./assets/scripts/Engine/EntityLoader.lua");
		(*state).require_file("sampleScene", "./assets/scripts/Client/sampleScene.lua");

		//Engine initialization
		(*state).script_file("./assets/scripts/Engine/Init.lua");

		//Components and systems definitions
		(*state).script_file("./assets/scripts/Client/ComponentsList.lua");
		(*state).script_file("./assets/scripts/Client/SystemsList.lua");

		(*state).script_file("./assets/scripts/Engine/test.lua"); //Test file of engine initialization, any other code goes below...
		PhysicsManager::getInstance()->setScriptManager(this); // Neded for collision callbacks
		return true;
	}

	bool ScriptManager::update()
	{
		entityManager->update();
		sol::protected_function_result result = (*state)["Manager"]["update"]((*state)["Manager"], 1);
		if (!result.valid()) {
			sol::error err = result;
			throw std::runtime_error(err.what());
		}
		(*state)["Update"]();
		//TODO exit state
		return true;
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
	}
	std::shared_ptr<Entity> ScriptManager::getEntity(UUID entityID)
	{
		return entityManager->getEntity(entityID);
	}
	void ScriptManager::sendCollisionEvent(UUID a, UUID b, const btManifoldPoint& manifold)
	{
		auto result = (*state)["Manager"]["eventManager"]["fireEvent"]((*state)["Manager"]["eventManager"],(*state)["reqNamespace"]["Collision"](a,b,manifold));
		if (!result.valid()) {
			sol::error err = result;
			throw std::runtime_error(err.what());
		}
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

		(*state).set_function("translateCamera", &PTSD::Camera::translate, PTSD::GraphicsManager::getInstance()->getCam());

		auto luaMeshComponent = (*state).new_usertype<PTSD::MeshComponent>("MeshComponent", sol::no_constructor);
		luaMeshComponent["setMesh"] = &PTSD::MeshComponent::setMesh;
		luaMeshComponent["setMaterial"] = &PTSD::MeshComponent::setMaterial;
		luaMeshComponent["getMesh"] = &PTSD::MeshComponent::getMesh;
		luaMeshComponent["getMaterial"] = &PTSD::MeshComponent::getMaterial;

		(*state).set_function("setMesh", [&](UUID id, const std::string& mesh, const std::string& mat) {
			return entityManager->getEntity(id).get()->addComponent<PTSD::MeshComponent>(mesh, mat);
			});

		(*state).set_function("translateCamera", &PTSD::Camera::translate, PTSD::GraphicsManager::getInstance()->getCam());
		(*state).set_function("getWindowWidth", &PTSD::GraphicsManager::getWindowWidth, PTSD::GraphicsManager::getInstance());
		(*state).set_function("getWindowHeight", &PTSD::GraphicsManager::getWindowHeight, PTSD::GraphicsManager::getInstance());
		(*state).set_function("rotateCamera", &PTSD::Camera::mouseRotate, PTSD::GraphicsManager::getInstance()->getCam());


		return true;
	}
	bool ScriptManager::bindPhysicsComponents()
	{
		//Init everything
		PTSD::LOG("Binding LUA Physics Components... @ScriptManager, BindPhysicsComponents()");

		auto luaRigidbodyComponent = (*state).new_usertype<PTSD::RigidbodyComponent>("RigidbodyComponent", sol::no_constructor);
		luaRigidbodyComponent["setLinearVelocity"] = &PTSD::RigidbodyComponent::setLinearVelocity;
		luaRigidbodyComponent["setAngularVelocity"] = &PTSD::RigidbodyComponent::setAngularVelocity;
		luaRigidbodyComponent["getLinearVelocity"] = &PTSD::RigidbodyComponent::getLinearVelocity;
		luaRigidbodyComponent["getAngularVelocity"] = &PTSD::RigidbodyComponent::getAngularVelocity;
		luaRigidbodyComponent["addForce"] = &PTSD::RigidbodyComponent::addForce;

		(*state).set_function("setRigidbody", [&](UUID id, Vec3 size, float mass, Vec3 pos, CollisionFlags type, bool trigger, Vec3 quat) {
			return entityManager->getEntity(id).get()->addComponent<PTSD::RigidbodyComponent>(size, mass, pos, type, trigger, quat);
			});
		(*state).set_function("setGravity", &PTSD::PhysicsManager::setGravity, PTSD::PhysicsManager::getInstance());
		(*state).new_enum<CollisionFlags>("CollisionFlags", {
			{"Dynamic", CollisionFlags::Dynamic},
			{"Static", CollisionFlags::Static},
			{"Kinematic", CollisionFlags::Kinematic}
			});
		auto manifold = (*state).new_usertype<btManifoldPoint>("manifold", sol::no_constructor);
		manifold["pointA"] = &btManifoldPoint::m_localPointA;
		manifold["pointB"] = &btManifoldPoint::m_localPointB;
		return true;
	}
	bool ScriptManager::bindSoundComponents()
	{
		PTSD::LOG("Binding LUA Sound Components... @ScriptManager, BindSoundComponents()");

		//Sound loading
		(*state).set_function("PTSDLoadSound", &PTSD::SoundManager::loadSound, PTSD::SoundManager::getInstance());

		//General-Use Sounds
		(*state).set_function("playSound", sol::resolve<int(int)>(&PTSD::SoundManager::playSound), PTSD::SoundManager::getInstance());

		//Music
		(*state).set_function("playMusic", sol::resolve<void(int, bool)>(&PTSD::SoundManager::playMusic), PTSD::SoundManager::getInstance());
		(*state).set_function("changeMusic", &PTSD::SoundManager::changeMusic, PTSD::SoundManager::getInstance());
		(*state).set_function("isMusicPaused", &PTSD::SoundManager::isMusicPaused, PTSD::SoundManager::getInstance());
		(*state).set_function("muteMusic", &PTSD::SoundManager::muteMusic, PTSD::SoundManager::getInstance());
		(*state).set_function("pauseMusic", &PTSD::SoundManager::pauseMusic, PTSD::SoundManager::getInstance());
		(*state).set_function("resumeMusic", &PTSD::SoundManager::resumeMusic, PTSD::SoundManager::getInstance());
		(*state).set_function("setMusicVolume", &PTSD::SoundManager::setMusicVolume, PTSD::SoundManager::getInstance());
		(*state).set_function("unmuteMusic", &PTSD::SoundManager::unmuteMusic, PTSD::SoundManager::getInstance());

		//Channel group management
		(*state).set_function("pauseChannelGroup", &PTSD::SoundManager::pauseChannelGroup, PTSD::SoundManager::getInstance());
		(*state).set_function("resumeChannelGroup", &PTSD::SoundManager::resumeChannelGroup, PTSD::SoundManager::getInstance());
		(*state).set_function("muteChannelGroup", &PTSD::SoundManager::muteChannelGroup, PTSD::SoundManager::getInstance());
		(*state).set_function("unmuteChannelGroup", &PTSD::SoundManager::unmuteChannelGroup, PTSD::SoundManager::getInstance());
		(*state).set_function("setChannelGroupVolume", &PTSD::SoundManager::setChannelGroupVolume, PTSD::SoundManager::getInstance());
		(*state).set_function("isChannelGroupPaused", &PTSD::SoundManager::isChannelGroupPaused, PTSD::SoundManager::getInstance());
		(*state).set_function("endChannelGroupSounds", &PTSD::SoundManager::endChannelGroupSounds, PTSD::SoundManager::getInstance());
		(*state).set_function("pauseChannel", &PTSD::SoundManager::pauseChannel, PTSD::SoundManager::getInstance());
		(*state).set_function("resumeChannel", &PTSD::SoundManager::resumeChannel, PTSD::SoundManager::getInstance());
		(*state).set_function("setChannelVolume", &PTSD::SoundManager::setChannelVolume, PTSD::SoundManager::getInstance());
		
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

		//Keys
		(*state).set_function("keyPressed", &PTSD::InputManager::keyPressed, PTSD::InputManager::getInstance());
		(*state).set_function("keyJustPressed", &PTSD::InputManager::keyJustDown, PTSD::InputManager::getInstance());
		(*state).set_function("keyRelease", &PTSD::InputManager::keyRelease, PTSD::InputManager::getInstance());
		(*state).set_function("keyJustReleased", &PTSD::InputManager::keyJustUp, PTSD::InputManager::getInstance());

		//Mouse
		(*state).set_function("getMouseRelativePosition", &PTSD::InputManager::getMouseRelativePosition, PTSD::InputManager::getInstance());
		(*state).set_function("resetMouse", &PTSD::InputManager::cleanMouseDelta, PTSD::InputManager::getInstance());
		(*state).set_function("mouseButtonPressed", &PTSD::InputManager::isMouseButtonDown, PTSD::InputManager::getInstance());
		(*state).set_function("mouseButtonJustReleased", &PTSD::InputManager::isMouseButtonJustUp, PTSD::InputManager::getInstance());
		(*state).set_function("mouseButtonJustPressed", &PTSD::InputManager::isMouseButtonJustDown, PTSD::InputManager::getInstance());

		//Gamepad
		(*state).set_function("controllerLeftTrigger", &PTSD::InputManager::controllerLeftTrigger, PTSD::InputManager::getInstance());
		(*state).set_function("controllerRightTrigger", &PTSD::InputManager::controllerRightTrigger, PTSD::InputManager::getInstance());
		(*state).set_function("controllerLeftAxis", &PTSD::InputManager::controllerLeftAxis, PTSD::InputManager::getInstance());
		(*state).set_function("controllerRightAxis", &PTSD::InputManager::controllerRightAxis, PTSD::InputManager::getInstance());
		(*state).set_function("controllerButtonPressed", &PTSD::InputManager::ControllerButtonPressed, PTSD::InputManager::getInstance());
		(*state).set_function("controllerButtonJustPressed", &PTSD::InputManager::ControllerButtonJustPressed, PTSD::InputManager::getInstance());

		//This should be expanded or reconsidered in the future.
		//Binding of the keybord keys
		(*state).new_enum<Scancode>("PTSDKeys", {
			{"W", Scancode::SCANCODE_W},
			{"A", Scancode::SCANCODE_A},
			{"S", Scancode::SCANCODE_S},
			{"D", Scancode::SCANCODE_D},
			{"H", Scancode::SCANCODE_H},
			{"J", Scancode::SCANCODE_J},
			{"Q", Scancode::SCANCODE_Q},
			{"R", Scancode::SCANCODE_R},
			{"F", Scancode::SCANCODE_F},
			{"Space", Scancode::SCANCODE_SPACE},
			{"Shift", Scancode::SCANCODE_LSHIFT}
			});
		//Mouse button enum
		(*state).new_enum<MouseButton>("PTSDMouseButton", {
			{"Left", MouseButton::Left},
			{"Middle", MouseButton::Middle},
			{"Right",  MouseButton::Right}
			});

			//Binding of the controller buttons
			(*state).new_enum<ControllerButton>("PTSDControllerButtons",{
				{"A",ControllerButton::CONTROLLER_BUTTON_A},
				{"B",ControllerButton::CONTROLLER_BUTTON_B},
				{"Y",ControllerButton::CONTROLLER_BUTTON_Y},
				{"START",ControllerButton::CONTROLLER_BUTTON_START}
			});


		return true;
	}
	bool ScriptManager::bindScriptingComponents() {
		(*state).set_function("PTSDCreateEntity", &PTSD::ScriptManager::createEntity, this);
		(*state).set_function("PTSDDeleteEntity", &PTSD::ScriptManager::deleteEntity, this);

		return true;
	}
	bool ScriptManager::bindGenericComponents()
	{
		//Init everything
		PTSD::LOG("Binding Generic Components... @ScriptManager, BindGenericComponents()");


		sol::usertype<PTSD::TransformComponent> trComponent = (*state).new_usertype<PTSD::TransformComponent>("Transform", sol::no_constructor);
		trComponent["translate"] = (void (PTSD::TransformComponent::*)(Vec3))(&PTSD::TransformComponent::translate);
		trComponent["position"] = sol::property(&PTSD::TransformComponent::getPosition, sol::resolve<void(Vec3)>(&PTSD::TransformComponent::setPosition));
		//Impressive development from Sol3

		(*state).set_function("setTransform", [&](UUID id, Vec3 p, Vec3 r, Vec3 s) {
			return entityManager->getEntity(id).get()->addComponent<TransformComponent>(p, r, s);
			});

		(*state).new_usertype<Vec3>("vec3", sol::constructors<Vec3(double, double, double),Vec3(float, float, float), Vec3(btVector3&)>(),"magnitude", &Vec3::magnitude,"normalize", &Vec3::normalize , "x", &Vec3::x, "y", &Vec3::y, "z", &Vec3::z, 
		sol::meta_function::multiplication, &Vec3::operator*,sol::meta_function::subtraction, &Vec3::operator-,sol::meta_function::addition, &Vec3::operator+);

		(*state).script("function vec3:__tostring__() return '{x: '..self.x ..' y:' .. self.y ' z:' .. self.z .. '} end'");
		(*state).new_usertype<Vector2D>("vec2", sol::constructors<Vector2D(double, double)>(), "x", &Vector2D::x, "y", &Vector2D::y, sol::meta_function::subtraction, &Vector2D::operator-,
			sol::meta_function::addition, &Vector2D::operator+, sol::meta_function::multiplication, &Vector2D::operator*);
		(*state).new_usertype<Vec4Placeholder>("vec4", sol::constructors<Vec4Placeholder(double, double, double, double)>(), "x", &Vec4Placeholder::x, "y", &Vec4Placeholder::y, "z", &Vec4Placeholder::z, "w", &Vec4Placeholder::w);
		return true;
	}
}