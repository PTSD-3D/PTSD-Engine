#pragma once
#include <sol/sol.hpp>
#include "lua.hpp"
#include "ECS.h"
#include "EntityManager.h"


namespace PTSD
{
	class ScriptingImplementation {
	private:
		sol::state state;
		EntityManager entityManager_;
		bool bindGraphicsComponents();
		bool bindPhysicsComponents();
		bool bindUIComponents();
		bool bindSoundComponents();
	public:
		ScriptingImplementation();
		virtual ~ScriptingImplementation() = default;

		void run(std::string scriptFile);

		bool init();
		bool update();
		void shutdown();

		Entity* createEntity();
		void deleteEntity(UUID entityID);
	};
}