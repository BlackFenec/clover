#ifndef ENGINE_H_
#define ENGINE_H_

#include "EngineState.h"
#include "ISystem.h"
#include "..\ui\Pane.h"
#include <thread>

class Engine
{
private:
	static Engine m_Engine;
	EngineState m_State;
	std::vector<ISystem*> m_Systems;
	std::thread * m_SystemsUpdateThread;
	Pane* m_Pane;

	void UpdateSystems();
public :
	Engine();
	virtual ~Engine();

	EngineState CurrentState();
	static Engine* GetInstance() { return &m_Engine; }
	void Start();
	void Stop();
};

#endif // !ENGINE_H_