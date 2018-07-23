#ifndef ENGINE_H_
#define ENGINE_H_

#include "ISystem.h"
#include <list>

class Engine
{
private:
	std::list<ISystem*> m_Systems;

public :
	Engine();
	virtual ~Engine();

	void Start();
};

#endif // !ENGINE_H_