#ifndef MOCKISERVER_H_
#define MOCKISERVER_H_
#include "gmock/gmock.h"
#include "../include/IServer.h"

class MockIServer : public IServer 
{
public:

	MOCK_METHOD0(Close, void());
	MOCK_METHOD1(ProcessClient, void(std::shared_ptr<IClientServer>));
	MOCK_METHOD0(Start, void());
};

#endif // !MOCKISERVER_H_