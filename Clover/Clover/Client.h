#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include "IClient.h"
#include <memory>

class Client : public IClient{
private:
	const std::string serverAdress = "localhost";
	const std::string serverPort = "27015";

public:
	Client(std::shared_ptr<ITcpSocket> s) {
		this->socket = s;
	};

	virtual void SendMessage(std::string message) {
		if (!message.empty()) this->socket->SendMessage(message);
	}

	virtual void Start() {
		this->socket->Initialize();
		this->socket->Create(serverAdress,serverPort);
	}
};

#endif