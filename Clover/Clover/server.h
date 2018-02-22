#ifndef SERVER_H_
#define SERVER_H_

#include "IServer.h"

class Server : public IServer{
public :
	
	Server(std::shared_ptr<ITcpSocket> s) {
		this->socket = s;
	};

	virtual void Start() {
		this->socket->Initialize();
	}
};

#endif // !SERVER_H_