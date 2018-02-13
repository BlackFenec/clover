#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <string>
#include "ITcpSocket.h"

class TcpSocket : public ITcpSocket{
public :
	virtual void SendMessage(std::string message)
	{

	}
};

#endif // !TCPSOCKET_H_