#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Entity.h"
#include "Rpc.h"
#include <map>

class EntityManager
{
private :
	std::map<UUID*, Entity*> m_Entities;

	EntityManager() {}

	EntityManager(const EntityManager &);
	EntityManager& operator=(const EntityManager &);
public :

	~EntityManager();

	static EntityManager* Instance();

	Entity* CreateEntity(int x, int y);
};
#endif // !ENTITYMANAGER_H_