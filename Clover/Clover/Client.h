#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>

class Client {

public :

	virtual void SendMessage(std::string message) = 0;
};

#endif