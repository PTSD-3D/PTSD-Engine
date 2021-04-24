#pragma once
#include <memory>
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

		bool bindLoggerComponents();
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

		std::shared_ptr<Entity> createEntity(UUID entityID);
		std::shared_ptr<Entity> getEntity(UUID entityID);
		void deleteEntity(UUID entityID);
	};
}