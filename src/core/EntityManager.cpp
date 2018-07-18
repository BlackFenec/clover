#include "EntityManager.h"
#include "..\physic\PositionComponent.h"

EntityManager EntityManager::m_EntityManager;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

Entity* EntityManager::CreateEntity(std::list<BaseComponent> components)
{
	Entity* entity = new Entity(components);
	m_Entities.insert(std::pair<UUID*,Entity*>(entity->GetUuid(), entity));
	return entity;
}