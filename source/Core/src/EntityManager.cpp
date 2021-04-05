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
