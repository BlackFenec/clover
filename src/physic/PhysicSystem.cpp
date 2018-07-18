#include "PhysicSystem.h"
#include "PositionComponent.h"
#include <iostream>

PhysicSystem::PhysicSystem()
{

}

PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Tick(std::list<BaseEntity*> entities)
{
	for (std::list<BaseEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		std::list<BaseComponent*> comps = (*it)->GetComponents();
		for (std::list<BaseComponent*>::iterator ct = comps.begin(); ct != comps.end(); ++ct)
		{
			if (PositionComponent* p = dynamic_cast<PositionComponent*>(*ct))
			{
				//TODO : Implement real movement logic
				std::cout << "Entity " << (*it)->GetUuid() << " with vector of length " << p->GetPosition().Length() << std::endl;
			}

		}
	}
}