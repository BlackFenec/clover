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
	const std::string k_ServerReceivingPort = "27015";
	const std::string k_ServerSendPort = "27016";
	std::map<std::shared_ptr<IClientServer>, std::thread*> m_SendingClients;
	std::map<std::shared_ptr<IClientServer>, std::thread*> m_ReceivingClients;

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

	virtual void ProcessReceivingClient(std::shared_ptr<IClientServer> client)
	{
		do
		{
			client->SendMessages();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		} while (!client->IsClosing());
		client->Shutdown();
		client->Close();
	}

	virtual void ProcessSendingClient(std::shared_ptr<IClientServer> client)
	{		
		do 
		{
			std::string response = client->ReceiveMessage();
			for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = this->m_ReceivingClients.begin(); it != this->m_ReceivingClients.end(); ++it)
			{
				(*it->first).QueueMessage(response);
			}
		} while (!client->IsClosing());
		client->Shutdown();
		client->Close();
	}

	void ListenSendingSockets()
	{
		this->m_Socket->Initialize();
		this->m_Socket->CreateServer(k_ServerSendPort);
		this->m_Socket->Bind();
		this->m_Socket->Listen();
		do
		{
			std::shared_ptr<SOCKET> client = this->m_Socket->Accept();
			if (client != nullptr)
			{
				std::shared_ptr<IClientServer> newClient(new ClientServer(client));
				m_SendingClients.insert(std::pair<std::shared_ptr<IClientServer>, std::thread*>(newClient, new std::thread(&Server::ProcessSendingClient, this, newClient)));
			}
		} while (!m_IsClosing);

		for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = m_SendingClients.begin(); it != m_SendingClients.end(); it++)
		{
			(*it->first).SetClosingState(true);
			(*it->second).join();
		}
		this->Close();
	}

	virtual void Run() 
	{
		new std::thread(&Server::ListenSendingSockets, this);
		this->m_Socket->Initialize();
		this->m_Socket->CreateServer(k_ServerReceivingPort);
		this->m_Socket->Bind();
		this->m_Socket->Listen();
		do
		{
			std::shared_ptr<SOCKET> client = this->m_Socket->Accept();
			if (client != nullptr)
			{
				std::shared_ptr<IClientServer> newClient(new ClientServer(client));
				m_ReceivingClients.insert(std::pair<std::shared_ptr<IClientServer>, std::thread*>(newClient, new std::thread(&Server::ProcessReceivingClient, this, newClient)));
			}
		} while (!m_IsClosing);

		for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = m_ReceivingClients.begin(); it != m_ReceivingClients.end(); it++)
		{
			(*it->first).SetClosingState(true);
			(*it->second).join();
		}

		this->Close();
	}
};

#endif // !SERVER_H_