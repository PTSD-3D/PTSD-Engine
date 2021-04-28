#pragma once
#include "Entity.h"
#include <unordered_map>
#include <memory>

namespace PTSD
{
	class Entity;
	using UUID = unsigned long;
	class EntityManager
	{
	private:
		std::unordered_map<UUID,std::shared_ptr<Entity>> entities_;
	public:
		EntityManager();
		~EntityManager();

		void init();
		void update();
		std::shared_ptr<Entity> createEntity(UUID entityID);
		std::shared_ptr<Entity> getEntity(UUID entityID);
		void deleteEntity(UUID entityID);
		
	};

}
