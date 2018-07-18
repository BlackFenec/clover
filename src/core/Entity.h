#ifndef ENTITY_H_
#define ENTITY_H_

#include "BaseEntity.h"
#include "..\physic\Vector2D.h"

class Entity : public BaseEntity
{

public :
	Entity();
	Entity(std::list<BaseComponent> components);

	virtual ~Entity();
};

#endif // !ENTITY_H_