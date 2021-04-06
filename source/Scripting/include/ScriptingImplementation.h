#pragma once
#include <sol/sol.hpp>
#include "lua.hpp"


namespace PTSD
{
	class ScriptingImplementation {
	private:
		sol::state state;
		bool bindGraphicsComponents();
		bool bindPhysicsComponents();
		bool bindUIComponents();
		bool bindSoundComponents();
		bool bindInputComponents();
	public:
		ScriptingImplementation();
		virtual ~ScriptingImplementation() = default;

		void run(std::string scriptFile);

		bool init();
		bool update();
		void shutdown();

		void addEntity(void* entityPtr);
		void deleteEntity(size_t entityID);
	};
}