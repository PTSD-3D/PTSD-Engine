#pragma once
#include "ObjectPool.h"
#include "Entity.h"

namespace PTSD
{
	class Entity;
	using UUID = unsigned long;
	class EntityManager
	{
	private:
		//TODO Entity pooling
		std::vector<Entity> entities_;
		UUID nextID_ = 0;
	public:
		EntityManager();
		~EntityManager();

		void init();
		void update();
		Entity* createEntity();
		
	};

}
