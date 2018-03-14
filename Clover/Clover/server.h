#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"

class Server : public IServer
{
private:
	const std::string k_Port = "27015";

public :
	
	Server(std::shared_ptr<ITcpSocket> s) {
		this->m_Socket = s;
	};

	virtual void Close() {
		this->m_Socket->Close();
	}

	virtual void Start() {
		this->m_Socket->Initialize();
		this->m_Socket->CreateServer(k_Port);
		this->m_Socket->Bind();
		this->m_Socket->Listen();
		this->m_Socket->Accept();
		std::string response = this->m_Socket->ReceiveFromClient();
		this->m_Socket->SendToClient(response);
		this->m_Socket->ShutdownClient();
		this->m_Socket->CloseClient();
	}
};

#endif // !SERVER_H_