#pragma once
#include <string>

namespace sol {
	class state;
}

namespace PTSD
{
	using UUID = unsigned long;
	class EntityManager;
	class Entity;
	class ScriptManager {
	private:
		sol::state* state;
		EntityManager* entityManager;

		bool bindGraphicsComponents();
		bool bindPhysicsComponents();
		bool bindUIComponents();
		bool bindSoundComponents();
		bool bindInputComponents();
		bool bindScriptingComponents();
		bool bindGenericComponents();
	public:
		ScriptManager();
		virtual ~ScriptManager();

		bool init();
		bool update();
		void shutdown();

		void run(const std::string& scriptFile);

		Entity* createEntity(UUID entityID);
		void deleteEntity(UUID entityID);
	};
}