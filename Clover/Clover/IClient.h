#ifndef ICLIENT_H_
#define ICLIENT_H_

#include <string>
#include "ITcpSocket.h"
#include <memory>

class IClient {
protected:
	std::shared_ptr<ITcpSocket> socket;

public:
	virtual ~IClient() {};
	IClient(){};

	virtual std::string SendMessage(std::string message) = 0;
	virtual void Start() = 0;
	virtual void Close() = 0;
};

#endif