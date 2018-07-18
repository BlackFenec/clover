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
	//{
	//	for (std::list<BaseEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	//	{
	//		std::list<BaseComponent*> comps = (*it)->GetComponents();
	//		for (std::list<BaseComponent*>::iterator ct = comps.begin(); ct != comps.end(); ++ct)
	//		{
	//			if (PositionComponent* p = dynamic_cast<PositionComponent*>(*ct))
	//			{
	//				//TODO : Implement real movement logic
	//				std::cout << "Entity " << (*it)->GetUuid() << " with vector of length " << p->GetPosition().Length() << std::endl;
	//			}

	//		}
	//	}
	//}
};

#endif