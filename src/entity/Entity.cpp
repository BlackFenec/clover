#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(std::vector<BaseComponent*> components) : BaseEntity(components)
{
	
}

Entity::~Entity()
{

}