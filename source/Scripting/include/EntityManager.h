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
		UUID nextID_ = 0;
	public:
		EntityManager();
		~EntityManager();

		void init();
		void update();
		Entity* createEntity();
		void deleteEntity(UUID entity);
		
	};

}
