#ifndef TALKINGCONTENT_H_
#define TALKINGCONTENT_H_

#include "MessageContent.h"
#include <string>

class TalkingContent : public MessageContent
{
private :
	std::string m_Message;

public :

	TalkingContent(std::string message);
	~TalkingContent();

	std::string GetMessage();
};

#endif // !TALKINGCONTENT_H_