#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Entity.h"
#include "Rpc.h"
#include <map>

class EntityManager
{
private :
	static EntityManager m_EntityManager;
	std::map<UUID*, Entity*> m_Entities;

public :
	EntityManager();
	virtual ~EntityManager();
	static EntityManager* GetInstance() { return &m_EntityManager; };

	Entity* CreateEntity(std::list<BaseComponent> components);
};
#endif // !ENTITYMANAGER_H_