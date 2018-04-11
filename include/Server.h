#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"
#include "ClientServer.h"
#include "Server.h"
#include <queue>
#include <thread>

class Server : public IServer
{
private:
	const std::string k_Port = "27015";
	std::vector<std::thread*> m_ClientThreads;
	std::vector<std::shared_ptr<IClientServer>> m_Clients;

public :
	
	Server(std::shared_ptr<ITcpSocket> s) : Server(s,false){};

	Server(std::shared_ptr<ITcpSocket> s, bool isClosing) {
		this->m_Socket = s;
		this->m_IsClosing = isClosing;
	};

	virtual ~Server() {};

	virtual void Close() {
		this->m_Socket->Close();
	}


	virtual void ProcessClient(std::shared_ptr<IClientServer> client)
	{
		
		while (true)//TODO CDA : Implement closing check
		{
			std::string response = client->ReceiveMessage();
			//TODO queue messages to all clients
			client->SendMessages();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		//
		//this->m_Socket->SendToClient(response, client);
	}


	virtual void Start() {
		this->m_Socket->Initialize();
		this->m_Socket->CreateServer(k_Port);
		this->m_Socket->Bind();
		this->m_Socket->Listen();
		do
		{
			std::shared_ptr<SOCKET> client = this->m_Socket->Accept();
			if (client != nullptr)
			{
				std::shared_ptr<IClientServer> newClient(new ClientServer(client));
				m_Clients.push_back(newClient);
				m_ClientThreads.push_back(new std::thread(&Server::ProcessClient, this, newClient));
			}
		} while (!m_IsClosing);

		for (std::vector<std::thread*>::iterator it = m_ClientThreads.begin(); it != m_ClientThreads.end(); it++)
			(*it)->join();

		this->Close();
	}
};

#endif // !SERVER_H_