#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "..\entity\Entity.h"
#include "Rpc.h"
#include <vector>

class EntityManager
{
private :
	static EntityManager m_EntityManager;
	std::vector<BaseEntity*> m_Entities;
	EntityManager();

public :
	virtual ~EntityManager();
	static EntityManager* GetInstance() { return &m_EntityManager; };

	Entity* CreateEntity(std::vector<BaseComponent*> components);
	std::vector<BaseEntity*> GetEntities();
};
#endif // !ENTITYMANAGER_H_