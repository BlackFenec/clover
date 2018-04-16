#ifndef ITCPSOCKET_H_
#define ITCPSOCKET_H_

#include <string>
#ifdef _WIN32
	#include <winsock2.h>
#else
	typedef unsigned int SOCKET;
#endif
#include <memory>

class ITcpSocket
{
public:
	ITcpSocket() {};
	virtual ~ITcpSocket() {};

	virtual std::shared_ptr<SOCKET> Accept() = 0;
	virtual void Bind() = 0;
	virtual void Close() = 0;
	virtual std::shared_ptr<SOCKET> ConnectToServer() = 0;
	virtual void CreateClient(std::string serverAdress, std::string serverPort) = 0;
	virtual void CreateServer(std::string port) = 0;
	virtual void Initialize() = 0;
	virtual void Listen() = 0;
	virtual std::string Receive() = 0;
	virtual void Send(std::string message) = 0;
	virtual void Shutdown() = 0;
};

#endif // !ITCPSOCKET_H_