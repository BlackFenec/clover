#include "PhysicSystem.h"
#include "PositionComponent.h"
#include <iostream>

PhysicSystem::PhysicSystem()
{

}

PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Tick(std::vector<BaseEntity*> entities)
{
	for (std::vector<BaseEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		std::vector<BaseComponent*> comps = (*it)->GetComponents();
		for (std::vector<BaseComponent*>::iterator ct = comps.begin(); ct != comps.end(); ++ct)
		{
			if (PositionComponent* p = dynamic_cast<PositionComponent*>(*ct))
			{
				p->Add(Vector2D(1, 1));
				std::cout << "Entity" << " at " << p->GetPosition() << std::endl;
			}
		}
	}
}