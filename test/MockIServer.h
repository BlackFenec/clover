#ifndef MOCKISERVER_H_
#define MOCKISERVER_H_
#include "gmock/gmock.h"
#include "../include/IServer.h"

class MockIServer : public IServer 
{
public:

	MOCK_METHOD0(Close, void());
	MOCK_METHOD0(ListenSendingSockets, void());
	MOCK_METHOD1(ProcessReceivingClient, void(std::shared_ptr<IClientServer>));
	MOCK_METHOD1(ProcessSendingClient, void(std::shared_ptr<IClientServer>));
	MOCK_METHOD0(Run, void());
};

#endif // !MOCKISERVER_H_