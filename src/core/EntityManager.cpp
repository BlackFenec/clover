#include "EntityManager.h"

EntityManager* EntityManager::Instance()
{
	static EntityManager instance;
	return &instance;
}

Entity* EntityManager::CreateEntity(int x, int y)
{
	Entity* entity = new Entity(x, y);
	m_Entities.insert(std::pair<UUID*,Entity*>(entity->GetUuid(), entity));
	return entity;
}