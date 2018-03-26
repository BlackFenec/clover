#ifndef CLIENT_H_
#define CLIENT_H_

#include "IClient.h"
#include <memory>

class Client : public IClient
{
private:

	const std::string k_ServerAddress = "localhost";
	const std::string k_ServerPort = "27015";

public:

	Client(std::shared_ptr<ITcpSocket> s) 
	{
		this->m_Socket = s;
	};

	virtual std::string Send(std::string message) 
	{
		std::string response;
		if (!message.empty())
		{
			this->m_Socket->Send(message);
			this->m_Socket->Shutdown();
			response = this->m_Socket->Receive();
			this->m_Socket->Close();
		}
		return response;
	}

	virtual void Start() 
	{
		this->m_Socket->Initialize();
		this->m_Socket->CreateClient(k_ServerAddress, k_ServerPort);
		this->m_Socket->ConnectToServer();
	}
};

#endif