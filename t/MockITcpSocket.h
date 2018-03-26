#ifndef MOCKITCPSOCKET_H_
#define MOCKITCPSOCKET_H_

#include "gmock\gmock.h"
#include "..\Clover\ITcpSocket.h"

class MockITcpSocket : public ITcpSocket
{
public:
	MOCK_METHOD0(Accept, std::shared_ptr<SOCKET>());
	MOCK_METHOD0(Bind, void());
	MOCK_METHOD0(Close, void());
	MOCK_METHOD1(CloseClient, void(std::shared_ptr<SOCKET> client));
	MOCK_METHOD0(ConnectToServer, void());
	MOCK_METHOD2(CreateClient, void(std::string serverAdress, std::string serverPort));
	MOCK_METHOD1(CreateServer, void(std::string port));
	MOCK_METHOD0(Initialize, void());
	MOCK_METHOD0(Listen, void());
	MOCK_METHOD0(Receive, std::string());
	MOCK_METHOD1(ReceiveFromClient, std::string(std::shared_ptr<SOCKET> client));
	MOCK_METHOD1(Send, void(std::string message));
	MOCK_METHOD2(SendToClient, void(std::string message, std::shared_ptr<SOCKET> client));
	MOCK_METHOD0(Shutdown, void());
	MOCK_METHOD1(ShutdownClient, void(std::shared_ptr<SOCKET> client));
};

#endif // !MOCKITCPSOCKET_H_