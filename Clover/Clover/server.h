#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"

class Server : public IServer{
private:
	const std::string port = "27015";
public :
	
	Server(std::shared_ptr<ITcpSocket> s) {
		this->socket = s;
	};

	virtual void Start() {
		this->socket->Initialize();
		this->socket->CreateServer(port);
		this->socket->Bind();
		this->socket->Listen();
		this->socket->Accept();
		//std::string response = this->socket->Receive();
		//this->socket->Send("Echo " + response);
	}

	virtual void Close() {
		this->socket->CloseClient();
		this->socket->Close();
	}

	virtual void CloseClient() {
		this->socket->CloseClient();
	}
};

#endif // !SERVER_H_