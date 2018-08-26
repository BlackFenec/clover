#include "Engine.h"
#include "..\physic\PhysicSystem.h"
#include "BaseEntity.h"
#include "EntityManager.h"

Engine::Engine()
{
	m_State = notInitialized;
	m_Systems.push_back(new PhysicSystem());
	m_State = stopped;
}

Engine::~Engine()
{
	if (m_State != stopped)
	{
		this->Stop();
		//TODO : Fix potential infinite loop if engine is stuck in stopping
	}
	for (std::vector<ISystem*>::iterator it = m_Systems.begin() ; it != m_Systems.end(); ++it)
	{
		delete *it;
	}
}

void Engine::Start()
{
	m_State = started;
	while (m_State != stopping && m_State != stopped)
	{
		//TODO : Some risk of concurrency with entities getting change between update.
		std::vector<BaseEntity*> entities = EntityManager::GetInstance()->GetEntities();
		for (std::vector<ISystem*>::iterator it = m_Systems.begin(); it != m_Systems.end(); ++it)
		{
			(*it)->Tick(entities);
		}
	}
}

void Engine::Stop()
{
	m_State = stopping;
	//TODO : implement system stopping when necessary
	m_State = stopped;
}

EngineState Engine::CurrentState()
{
	return m_State;
}