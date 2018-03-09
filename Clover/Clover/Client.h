#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include "IClient.h"
#include <memory>

class Client : public IClient
{
private:

	const std::string serverAdress = "localhost";
	const std::string serverPort = "27015";

public:
	Client(std::shared_ptr<ITcpSocket> s) 
	{
		this->socket = s;
	};

	virtual std::string Send(std::string message) 
	{
		std::string response;
		if (!message.empty())
		{
			this->socket->Send(message);
			this->socket->Shutdown();
			response = this->socket->Receive();
			this->socket->Close();
		}
		return response;
	}

	virtual void Start() 
	{
		this->socket->Initialize();
		this->socket->CreateClient(serverAdress,serverPort);
		this->socket->ConnectToServer();
	}
};

#endif