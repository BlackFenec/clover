#include "PositionComponent.h"

PositionComponent::PositionComponent()
{
	this->m_Position = Vector2D();
}

PositionComponent::PositionComponent(double x, double y)
{
	this->m_Position = Vector2D(x, y);
}

PositionComponent::~PositionComponent()
{

}

Vector2D PositionComponent::GetPosition()
{
	return m_Position;
}

void PositionComponent::Add(Vector2D v)
{
	this->m_Position = this->m_Position + v;
}