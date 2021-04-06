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
		ent.init();
}

void PTSD::EntityManager::update()
{
	for (auto& ent : entities_)
		ent.update();
}

PTSD::Entity* PTSD::EntityManager::createEntity()
{
	entities_.push_back({nextID_++});
	return &entities_.back();
}

void PTSD::EntityManager::deleteEntity(UUID entity)
{
	auto it = entities_.begin();
	while (it != entities_.end())
		++it;
	if(it==entities_.end())
	{
		PTSD::LOG("UNABLE TO FOUND ENTITY", Error);
		throw "Entity not found";
	}
	entities_.erase(it);
}
