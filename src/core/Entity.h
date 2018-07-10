#ifndef ENTITY_H_
#define ENTITY_H_

#include "BaseEntity.h"

class Entity : public BaseEntity
{
private :
	int m_PositionX;
	int m_PositionY;

public :
	Entity()
	{
		this->m_PositionX = 0;
		this->m_PositionY = 0;
	}

	Entity(int x, int y)
	{
		this->m_PositionX = x;
		this->m_PositionY = y;
	}

	virtual ~Entity();

	UUID GetUuid()
	{
		return m_Uuid;
	}

};

#endif // !ENTITY_H_