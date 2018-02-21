#ifndef ISERVER_H_
#define ISERVER_H_

#include <memory>
#include "ITcpSocket.h"

class IServer {
protected:
	std::shared_ptr<ITcpSocket> socket;
public:

	virtual ~IServer() {};
	IServer() {};
	virtual void Start() = 0;

};

#endif // !ISERVER_H_