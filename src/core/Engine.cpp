#include "Engine.h"
#include "..\physic\PhysicSystem.h"
#include "BaseEntity.h"
#include "EntityManager.h"

Engine::Engine()
{
	m_Systems.push_back(new PhysicSystem());
}

Engine::~Engine()
{
	for (std::list<ISystem*>::iterator it = m_Systems.begin() ; it != m_Systems.end(); ++it)
	{
		delete *it;
	}
}

void Engine::Start()
{
	while (true)
	{
		//TODO : Some risk of concurrency with entities getting change between update.
		std::list<BaseEntity*> entities = EntityManager::GetInstance()->GetEntities();
		for (std::list<ISystem*>::iterator it = m_Systems.begin(); it != m_Systems.end(); ++it)
		{
			(*it)->Tick(entities);
		}
	}
}