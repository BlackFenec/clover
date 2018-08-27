#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "..\core\BaseEntity.h"
#include "MessageContent.h"
#include "MessageType.h"

class Message
{
private :
	BaseEntity * m_Source;
	BaseEntity * m_Target;
	MessageType m_Type;
	MessageContent * m_Content;

public :
	Message(BaseEntity * source, BaseEntity * target, MessageType type, MessageContent * content);
	virtual ~Message();

	BaseEntity* GetSource();
	BaseEntity* GetTarget();
	MessageType GetType();
	MessageContent* GetContent();
};

#endif // !MESSAGE_H_