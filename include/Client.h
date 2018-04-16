#ifndef CLIENT_H_
#define CLIENT_H_

#include "ClientServer.h"
#include "IClient.h"
#include <fstream>
#include <memory>
#include <thread>

class Client : public IClient
{
private:

	std::shared_ptr<IClientServer> m_Client;
	std::shared_ptr<std::ofstream> m_Output;
	const std::string k_ServerAddress = "localhost";
	const std::string k_ServerPort = "27015";
	std::thread * m_SocketProcessing;

public:

	Client(std::shared_ptr<ITcpSocket> s, std::shared_ptr<std::ofstream> output) 
	{
		this->m_Output = output;
		this->m_Socket = s;
	};

	virtual void ProcessClient(std::shared_ptr<IClientServer> client)
	{
		while (client->IsClosing())
		{
			std::string response = client->ReceiveMessage();
			*this->m_Output << response << std::endl;
			client->SendMessages();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		client->Shutdown();
		client->Close();
	}

	virtual void Send(std::string message) 
	{
		this->m_Client->QueueMessage(message);
	}

	virtual void Start() 
	{
		this->m_Socket->Initialize();
		this->m_Socket->CreateClient(k_ServerAddress, k_ServerPort);
		std::shared_ptr<SOCKET> client = this->m_Socket->ConnectToServer();
		if (client != nullptr)
		{
			std::shared_ptr<IClientServer> newClient(new ClientServer(client));
			this->m_Client = newClient;
			this->m_SocketProcessing = new std::thread(&Client::ProcessClient, this, this->m_Client);
		}
	}
};

#endif