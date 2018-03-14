#ifndef ISERVER_H_
#define ISERVER_H_

#include "ITcpSocket.h"
#include <memory>

class IServer 
{
protected:
	std::shared_ptr<ITcpSocket> m_Socket;

public:
	IServer() {};
	virtual ~IServer() {};

	virtual void Close() = 0;
	virtual void Start() = 0;
};

#endif // !ISERVER_H_