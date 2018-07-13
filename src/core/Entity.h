#ifndef ENTITY_H_
#define ENTITY_H_

#include "BaseEntity.h"

class Entity : public BaseEntity
{
private :
	int m_PositionX;
	int m_PositionY;

public :
	Entity(int x, int y);

	virtual ~Entity();
};

#endif // !ENTITY_H_