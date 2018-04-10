#ifndef CHATSERVER_H_
#define CHATSERVER_H_

#include "Server.h"

class ChatServer : public Server
{
protected:
	virtual void ProcessClient(std::shared_ptr<SOCKET> client) override
	{
		std::string response = this->m_Socket->ReceiveFromClient(client);
		this->m_Socket->SendToClient(response, client);
	}

public:

	ChatServer(std::shared_ptr<ITcpSocket> s) : Server(s, false) {};

	ChatServer(std::shared_ptr<ITcpSocket> s, bool isClosing) : Server(s, isClosing) {};

	virtual ~ChatServer() {};
};

#endif // !CHATSERVER_H_