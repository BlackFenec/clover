#ifndef ICLIENT_H_
#define ICLIENT_H_

#include "IClientServer.h"
#include "ITcpSocket.h"
#include <memory>

class IClient 
{
protected:

	std::shared_ptr<IClientServer> m_Client;
	std::shared_ptr<ITcpSocket> m_Socket;

public:
	IClient() {};
	virtual ~IClient() {};

	virtual std::shared_ptr<IClientServer> GetClientServer() = 0;
	virtual void ProcessClient(std::shared_ptr<IClientServer> client) = 0;
	virtual void Send(std::string message) = 0;
	virtual void SetClientServer(std::shared_ptr<IClientServer> client) = 0;
	virtual void Start() = 0;
};

#endif