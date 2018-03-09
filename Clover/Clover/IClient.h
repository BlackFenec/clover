#ifndef ICLIENT_H_
#define ICLIENT_H_

#include <string>
#include "ITcpSocket.h"
#include <memory>

class IClient 
{
protected:
	std::shared_ptr<ITcpSocket> socket;

public:
	virtual ~IClient() {};
	IClient(){};

	virtual std::string Send(std::string message) = 0;
	virtual void Start() = 0;
};

#endif