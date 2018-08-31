#include "Server.h"

Server::Server(std::shared_ptr<ITcpSocket> receivingSocket, std::shared_ptr<ITcpSocket> sendingSocket) : Server(receivingSocket, sendingSocket, false) 
{

}

Server::Server(std::shared_ptr<ITcpSocket> receivingSocket, std::shared_ptr<ITcpSocket> sendingSocket, bool isClosing)
{
	this->m_ReceivingSocket = receivingSocket;
	this->m_SendingSocket = sendingSocket;
	this->m_IsClosing = isClosing;
}

Server::~Server()
{
	for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = m_ReceivingClients.begin(); it != m_ReceivingClients.end(); ++it)
		delete it->second;
	for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = m_SendingClients.begin(); it != m_SendingClients.end(); ++it)
		delete it->second;
}

void Server::Close()
{
	this->m_IsClosing = true;
}

void Server::ListenReceivingSockets()
{
	this->m_ReceivingSocket->Initialize();
	this->m_ReceivingSocket->CreateServer(k_ServerReceivingPort);
	this->m_ReceivingSocket->Bind();
	this->m_ReceivingSocket->Listen();
	do
	{
		std::shared_ptr<SOCKET> client = this->m_ReceivingSocket->Accept();
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

	this->m_ReceivingSocket->Close();
}

void Server::ListenSendingSockets()
{
	this->m_SendingSocket->Initialize();
	this->m_SendingSocket->CreateServer(k_ServerSendPort);
	this->m_SendingSocket->Bind();
	this->m_SendingSocket->Listen();
	do
	{
		std::shared_ptr<SOCKET> client = this->m_SendingSocket->Accept();
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
	this->m_SendingSocket->Close();
}

void Server::ProcessReceivingClient(std::shared_ptr<IClientServer> client)
{
	do
	{
		client->SendMessages();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (!client->IsClosing());
	client->Shutdown();
	client->Close();
	for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = this->m_ReceivingClients.begin(); it != this->m_ReceivingClients.end(); ++it)
	{
		if ((it->first) == client)
		{
			m_ReceivingClients.erase(it);
			break;
		}
	}
}

void Server::ProcessSendingClient(std::shared_ptr<IClientServer> client)
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
	for (std::map<std::shared_ptr<IClientServer>, std::thread*>::iterator it = this->m_SendingClients.begin(); it != this->m_SendingClients.end(); ++it)
	{
		if ((it->first) == client)
		{
			m_SendingClients.erase(it);
			break;
		}
	}
}

void Server::Run()
{
	new std::thread(&Server::ListenSendingSockets, this);
	this->ListenReceivingSockets();
}