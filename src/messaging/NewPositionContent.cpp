#include "NewPositionContent.h"

NewPositionContent::NewPositionContent(PositionComponent * position) : MessageContent()
{
	this->m_Position = position;
}

NewPositionContent::~NewPositionContent()
{
	delete this->m_Position;
}

PositionComponent* NewPositionContent::GetPosition()
{
	return m_Position;
}