#ifndef ITCPSOCKET_H_
#define ITCPSOCKET_H_

#include <string>

class ITcpSocket
{
public:
	virtual ~ITcpSocket() {}
	virtual void SendMessage(std::string message) = 0;
};

#endif // !ITCPSOCKET_H_