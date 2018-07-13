#include "Entity.h"

Entity::Entity(int x, int y) :m_PositionX(x), m_PositionY(y)
{
	this->m_PositionX = x;
	this->m_PositionY = y;
}

Entity::~Entity()
{

}