#ifndef PHYSICSYSTEM_H_
#define PHYSICSYSTEM_H_

#include "..\core\ISystem.h"
#include "PositionComponent.h"
#include <iostream>

class PhysicSystem : public ISystem
{
public :
	PhysicSystem();
	virtual ~PhysicSystem();

	void Tick(std::list<BaseEntity*> entities);
};

#endif