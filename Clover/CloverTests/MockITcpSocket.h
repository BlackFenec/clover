#ifndef MOCKITCPSOCKET_H_
#define MOCKITCPSOCKET_H_
#include "gmock\gmock.h"
#include "..\Clover\ITcpSocket.h"

class MockITcpSocket : public ITcpSocket{
public:
	MOCK_METHOD1(SendMessage, void(std::string message));
	MOCK_METHOD0(Initialize, void());
};

#endif // !MOCKITCPSOCKET_H_