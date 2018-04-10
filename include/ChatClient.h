#ifndef CHATCLIENT_H_
#define CHATCLIENT_H_

#include "Client.h"
#include <memory>

class ChatClient : public Client
{
public:

	ChatClient(std::shared_ptr<ITcpSocket> s) : Client(s){};

	~ChatClient() {};
};

#endif // !CHATCLIENT_H_