#pragma once
#include "Entity.h"

namespace PTSD
{
	class Entity;
	using UUID = unsigned long;
	class EntityManager
	{
	private:
		std::vector<Entity> entities_;
	public:
		EntityManager();
		~EntityManager();

		void init();
		void update();
		Entity* createEntity(UUID entityID);
		void deleteEntity(UUID entityID);
		
	};

}
