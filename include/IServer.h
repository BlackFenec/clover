#ifndef ISERVER_H_
#define ISERVER_H_

#include "ITcpSocket.h"
#include "IClientServer.h"
#include <memory>

class IServer 
{
protected:
	std::shared_ptr<ITcpSocket> m_ReceivingSocket;
	std::shared_ptr<ITcpSocket> m_SendingSocket;
	bool m_IsClosing;

public:
	IServer() {};
	virtual ~IServer() {};

	virtual void Close() = 0;
	virtual void ListenSendingSockets() = 0;
	virtual void ProcessReceivingClient(std::shared_ptr<IClientServer> client) = 0;
	virtual void ProcessSendingClient(std::shared_ptr<IClientServer> client) = 0;
	virtual void Run() = 0;
};

#endif // !ISERVER_H_