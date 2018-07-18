#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(std::list<BaseComponent*> components) : BaseEntity(components)
{
	
}

Entity::~Entity()
{

}