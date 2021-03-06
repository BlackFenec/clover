#ifndef MOCKITCPSOCKET_H_
#define MOCKITCPSOCKET_H_

#include "gmock/gmock.h"
#include "../../src/network/ITcpSocket.h"

class MockITcpSocket : public ITcpSocket
{
public:
	MOCK_METHOD0(Accept, std::shared_ptr<SOCKET>());
	MOCK_METHOD0(Bind, void());
	MOCK_METHOD0(Close, void());
	MOCK_METHOD0(ConnectToServer, std::shared_ptr<SOCKET>());
	MOCK_METHOD2(CreateClient, void(std::string serverAdress, std::string serverPort));
	MOCK_METHOD1(CreateServer, void(std::string port));
	MOCK_METHOD0(Initialize, void());
	MOCK_METHOD0(Listen, void());
	MOCK_METHOD0(Receive, std::string());
	MOCK_METHOD1(Send, void(std::string message));
	MOCK_METHOD0(Shutdown, void());
};

#endif // !MOCKITCPSOCKET_H_