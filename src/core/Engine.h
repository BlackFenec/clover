#ifndef ENGINE_H_
#define ENGINE_H_

#include "EngineState.h"
#include "ISystem.h"
#include <list>

class Engine
{
private:
	std::list<ISystem*> m_Systems;
	EngineState m_State;

public :
	Engine();
	virtual ~Engine();

	void Start();
	void Stop();
};

#endif // !ENGINE_H_