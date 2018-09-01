#ifndef ENGINE_H_
#define ENGINE_H_

#include "EngineState.h"
#include "ISystem.h"
#include "..\ui\Pane.h"
#include <thread>

class Engine
{
private:
	std::vector<ISystem*> m_Systems;
	EngineState m_State;
	Pane * m_Window;
	std::thread * m_SystemsUpdateThread;

	void UpdateSystems();
public :
	Engine();
	virtual ~Engine();

	void Start();
	void Stop();
	EngineState CurrentState();
};

#endif // !ENGINE_H_