#include "EntityManager.h"

EntityManager EntityManager::m_EntityManager;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

Entity* EntityManager::CreateEntity(int x, int y)
{
	Entity* entity = new Entity(Vector2D(x,y));
	m_Entities.insert(std::pair<UUID*,Entity*>(entity->GetUuid(), entity));
	return entity;
}