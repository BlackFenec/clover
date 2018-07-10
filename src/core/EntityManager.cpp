#include "EntityManager.h"

static EntityManager* EntityManager::Instance()
{
	static EntityManager instance;
	return &instance;
}

Entity* EntityManager::CreateEntity(int x, int y)
{
	Entity* entity = new Entity(x, y);
	m_Entities.insert(entity->GetUuid(), entity);
}