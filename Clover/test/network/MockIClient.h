#ifndef MOCKICLIENT_H_
#define MOCKICLIENT_H_
#include "gmock/gmock.h"
#include "../../src/network/IClient.h"

class MockIClient : public IClient 
{
public:

	MOCK_METHOD0(GetClientServer, std::shared_ptr<IClientServer>());
	MOCK_METHOD1(ProcessClient, void(std::shared_ptr<IClientServer>));
	MOCK_METHOD1(Send, void(std::string));
	MOCK_METHOD1(SetClientServer, void(std::shared_ptr<IClientServer>));
	MOCK_METHOD0(Start, void());
};

#endif // !MOCKICLIENT_H_