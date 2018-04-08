#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"
#include <queue>
#include <thread>

class Server : public IServer
{
private:
	const std::string k_Port = "27015";
	std::vector<std::thread*> m_Clients;

	void ProcessClient(std::shared_ptr<SOCKET> client)
	{
		std::string response = this->m_Socket->ReceiveFromClient(client);
		this->m_Socket->SendToClient(response, client);
	}

public :
	
	Server(std::shared_ptr<ITcpSocket> s) : Server(s,false){};

	Server(std::shared_ptr<ITcpSocket> s, bool isClosing) {
		this->m_Socket = s;
		this->m_IsClosing = isClosing;
	};

	virtual void Close() {
		this->m_Socket->Close();
	}

	virtual void Start() {
		this->m_Socket->Initialize();
		this->m_Socket->CreateServer(k_Port);
		this->m_Socket->Bind();
		this->m_Socket->Listen();
		do
		{
			m_Clients.push_back(new std::thread(&Server::ProcessClient, this, this->m_Socket->Accept()));
		} while (!m_IsClosing);

		for (std::vector<std::thread*>::iterator it = m_Clients.begin(); it != m_Clients.end(); it++)
			(*it)->join();

		this->Close();
	}
};

#endif // !SERVER_H_