#ifndef MOCKICLIENTSERVER_H_
#define MOCKICLIENTSERVER_H_
#include "gmock/gmock.h"
#include "../../src/network/IClientServer.h"

class MockIClientServer : public IClientServer
{
public:

	MOCK_METHOD0(Close, void());
	MOCK_METHOD0(IsClosing, bool());
	MOCK_METHOD1(QueueMessage, void(std::string));
	MOCK_METHOD0(ReceiveMessage, std::string());
	MOCK_METHOD0(SendMessages, void());
	MOCK_METHOD1(SetClosingState, void(bool));
	MOCK_METHOD0(Shutdown, void());
};

#endif // !MOCKICLIENTSERVER_H_