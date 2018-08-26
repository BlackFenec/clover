#include "EntityManager.h"
#include "..\physic\PositionComponent.h"

EntityManager EntityManager::m_EntityManager;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	for (std::vector<BaseEntity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
	{
		delete *it;
	}
}

Entity* EntityManager::CreateEntity(std::vector<BaseComponent*> components)
{
	Entity* entity = new Entity(components);
	m_Entities.push_back(entity);
	return entity;
}

std::vector<BaseEntity*> EntityManager::GetEntities()
{
	return m_Entities;
}