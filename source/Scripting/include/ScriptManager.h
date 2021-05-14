#pragma once
#include <memory>
#include <string>

namespace sol {
	class state;
}
class btManifoldPoint;
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
		void execute(const std::string& functionName);
		void sendCollisionEvent(UUID, UUID, const btManifoldPoint&);
		std::shared_ptr<Entity> createEntity(UUID entityID);
		std::shared_ptr<Entity> getEntity(UUID entityID);
		void deleteEntity(UUID entityID);
	};
}