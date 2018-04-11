#ifndef ISERVER_H_
#define ISERVER_H_

#include "ITcpSocket.h"
#include <IClientServer.h>
#include <memory>

class IServer 
{
protected:
	std::shared_ptr<ITcpSocket> m_Socket;
	bool m_IsClosing;

public:
	IServer() {};
	virtual ~IServer() {};

	virtual void Close() = 0;
	virtual void ProcessClient(std::shared_ptr<IClientServer> client) = 0;
	virtual void Start() = 0;
};

#endif // !ISERVER_H_