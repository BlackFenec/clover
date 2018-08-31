#include "TalkingContent.h"

TalkingContent::TalkingContent(std::string message) : MessageContent()
{
	this->m_Message = message;
}

TalkingContent::~TalkingContent()
{

}

std::string TalkingContent::GetMessage()
{
	return this->m_Message;
}