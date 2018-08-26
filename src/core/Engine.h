#ifndef ENGINE_H_
#define ENGINE_H_

#include "EngineState.h"
#include "ISystem.h"

class Engine
{
private:
	std::vector<ISystem*> m_Systems;
	EngineState m_State;

public :
	Engine();
	virtual ~Engine();

	void Start();
	void Stop();
	EngineState CurrentState();
};

#endif // !ENGINE_H_