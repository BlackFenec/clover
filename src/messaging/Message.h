#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "..\core\BaseEntity.h"
#include "MessageType.h"

class Message
{
private :
	BaseEntity * source;
	BaseEntity * target;
	MessageType type;

public :
	Message(BaseEntity * source, BaseEntity * target);
	virtual ~Message();
};

#endif // !MESSAGE_H_