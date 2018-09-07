#include "Engine.h"
#include "..\physic\PhysicSystem.h"
#include "BaseEntity.h"
#include "EntityManager.h"

Engine Engine::m_Engine;

Engine::Engine()
{
	m_State = notInitialized;
	m_Systems.push_back(new PhysicSystem());
	m_Window = new Pane();
	m_State = started;
}

Engine::~Engine()
{
	if (m_State != stopped)
	{
		this->Stop();
	}

	delete m_Window;
	delete m_SystemsUpdateThread;

	for (std::vector<ISystem*>::iterator it = m_Systems.begin() ; it != m_Systems.end(); ++it)
	{
		delete *it;
	}
}

EngineState Engine::CurrentState()
{
	return m_State;
}

void Engine::Start()
{
	m_State = started;	
	m_SystemsUpdateThread = new std::thread(&Engine::UpdateSystems, this);
	m_Window->Show();
}

void Engine::Stop()
{
	if (m_State == stopping || m_State == stopped) return;
	m_State = stopping;
	m_SystemsUpdateThread->join();
	m_State = stopped;
}

void Engine::UpdateSystems()
{
	while (m_State != stopping && m_State != stopped)
	{
		std::vector<BaseEntity*> entities = EntityManager::GetInstance()->GetEntities();
		for (std::vector<ISystem*>::iterator it = m_Systems.begin(); it != m_Systems.end(); ++it)
		{
			(*it)->Tick(entities);
		}
	}
}