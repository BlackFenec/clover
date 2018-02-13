#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include "IClient.h"
#include <memory>

class Client : public IClient{
public:
	Client(std::shared_ptr<ITcpSocket> s) {
		this->socket = s;
	};

	virtual void SendMessage(std::string message) {
		this->socket->SendMessage(message);
	}
};

#endif