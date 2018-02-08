#ifndef ICLIENT_H_
#define ICLIENT_H_

#include <string>
#include "ITcpSocket.h"

class IClient {
private:
	//ITcpSocket socket;

public:
	virtual ~IClient() {}
	virtual void SendMessage(std::string message) = 0;
};

#endif