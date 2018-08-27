#ifndef NEWPOSITIONCONTENT_H_
#define NEWPOSITIONCONTENT_H_

#include "MessageContent.h"
#include "..\physic\PositionComponent.h"

class NewPositionContent : public MessageContent
{
private :
	PositionComponent * m_Position;

public :
	NewPositionContent(PositionComponent * position);
	~NewPositionContent();

	PositionComponent* GetPosition();
};

#endif // !NEWPOSITIONCONTENT_H_