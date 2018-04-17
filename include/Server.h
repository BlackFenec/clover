#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"
#include "ClientServer.h"
#include "Server.h"
#include <map>
#include <queue>
#include <thread>

class Server : public IServer
{
private:
	const std::string k_Port = "27015";
	std::map<std::shared_ptr<IClientServer>,std::thread*> m_Clients;

public :
	
	Server(std::shared_ptr<ITcpSocket> s) : Server(s,false){};

	Server(std::shared_ptr<ITcpSocket> s, bool isClosing) 
	{
		this->m_Socket = s;
		this->m_IsClosing = isClosing;
	};

	virtual ~Server() {};

	virtual void Close() 
	{
		this->m_Socket->Close();
	}

	virtual void ProcessClient(std::shared_ptr<IClientServer> client)
	{		
		while (!client->IsClosing())
		{
			std::string response = client->ReceiveMessage();
			for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = this->m_Clients.begin(); it != this->m_Clients.end(); ++it)
			{
				printf("queueing");
				if (it->first != client) 
					(*it->first).QueueMessage(response);
			}
				

			client->SendMessages();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		client->Shutdown();
		client->Close();
	}

	virtual void Start() 
	{
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
				m_Clients.insert(std::pair<std::shared_ptr<IClientServer>, std::thread*>(newClient, new std::thread(&Server::ProcessClient, this, newClient)));
			}
		} while (!m_IsClosing);

		for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = m_Clients.begin(); it != m_Clients.end(); it++)
		{
			(*it->first).SetClosingState(true);
			(*it->second).join();
		}

		this->Close();
	}
};

#endif // !SERVER_H_