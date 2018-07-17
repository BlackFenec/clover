#ifndef ENTITY_H_
#define ENTITY_H_

#include "BaseEntity.h"
#include "..\physic\Vector2D.h"

class Entity : public BaseEntity
{
private :
	Vector2D m_Position;

public :
	Entity();
	Entity(Vector2D position);

	virtual ~Entity();
};

#endif // !ENTITY_H_