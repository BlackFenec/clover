#include "Message.h"

Message::Message(BaseEntity * source, BaseEntity * target, MessageType type, MessageContent * content)
{
	this->m_Source = source;
	this->m_Target = target;
	this->m_Type = type;
	this->m_Content = content;
}

Message::~Message()
{
	delete m_Content;
}

BaseEntity* Message::GetSource()
{
	return m_Source;
}

BaseEntity* Message::GetTarget()
{
	return m_Target;
}

MessageType Message::GetType()
{
	return m_Type;
}

MessageContent* Message::GetContent()
{
	return m_Content;
}