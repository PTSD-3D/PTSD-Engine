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

void PTSD::EntityManager::deleteEntity(UUID entityID)
{
	auto it = entities_.find(entityID);
	if(it!=entities_.end())
	{
		entities_.erase(it);
	}
}
