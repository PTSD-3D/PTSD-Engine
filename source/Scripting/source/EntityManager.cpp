#pragma once
#include "EntityManager.h"
#include "Entity.h"

PTSD::EntityManager::EntityManager()
{
}

PTSD::EntityManager::~EntityManager()
{
}

void PTSD::EntityManager::init()
{
	for (auto& ent : entities_)
		ent.second->init();
}

void PTSD::EntityManager::update()
{
	for (auto& ent : entities_)
		ent.second->update();
}

std::shared_ptr<PTSD::Entity> PTSD::EntityManager::createEntity(UUID entityID)
{
	auto ent = entities_.insert({ entityID,std::make_shared<Entity>(entityID) });
	return ent.first->second;
}
std::shared_ptr<PTSD::Entity> PTSD::EntityManager::getEntity(UUID entityID)
{
	return entities_[entityID];
}
void PTSD::EntityManager::deleteEntity(UUID entityID)
{
	auto it = entities_.find(entityID);
	if(it!=entities_.end())
	{
		//We make sure we hide the node and delete the rigibody before the trash collector takes care of everything else
		//this is because if we wait there might be problems if we have to wait for the whole system to delete each individual component
		it->second->disableEntity();
		entities_.erase(it);
	}
}
