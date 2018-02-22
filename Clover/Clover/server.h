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
		this->socket->Create(port);
		this->socket->Bind();
		this->socket->Listen();
		this->socket->Accept();
	}
};

#endif // !SERVER_H_