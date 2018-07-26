#include "Client.h"

Client::Client(std::shared_ptr<ITcpSocket> s, std::shared_ptr<std::ostream> output)
{
	this->m_Output = output;
	this->m_Socket = s;
}

Client::~Client()
{

}

std::shared_ptr<IClientServer> Client::GetClientServer()
{
	return this->m_Client;
}

void Client::ProcessClient(std::shared_ptr<IClientServer> client)
{
	while (!client->IsClosing())
	{
		std::string response = client->ReceiveMessage();
		*this->m_Output << std::endl << "Server : " << response << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	client->Shutdown();
	client->Close();
}

void Client::Send(std::string message)
{
	if (this->m_Client == nullptr) this->SetUpClient();
	this->m_Client->QueueMessage(message);
	this->m_Client->SendMessages();
}

void Client::SetClientServer(std::shared_ptr<IClientServer> client)
{
	this->m_Client = client;
}

void Client::SetUpClient()
{
	this->m_Socket->Initialize();
	this->m_Socket->CreateClient(k_ServerAddress, k_ServerSendPort);
	std::shared_ptr<SOCKET> client = this->m_Socket->ConnectToServer();
	if (client == nullptr) throw std::exception("no socket available");

	std::shared_ptr<IClientServer> newSendingClient(new ClientServer(client));
	this->m_Client = newSendingClient;
}

void Client::Start()
{
	this->m_Socket->Initialize();
	this->m_Socket->CreateClient(k_ServerAddress, k_ServerReceivingPort);
	std::shared_ptr<SOCKET> client = this->m_Socket->ConnectToServer();
	if (client == nullptr) throw std::exception("no socket available");

	std::shared_ptr<IClientServer> newReceivingClient(new ClientServer(client));
	this->m_SocketProcessing = new std::thread(&Client::ProcessClient, this, newReceivingClient);
}