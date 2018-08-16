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
				p->Add(Vector2D(1, 1));
				std::cout << "Entity " << (*it)->GetUuid() << " at " << p->GetPosition() << std::endl;
			}
		}
	}
}