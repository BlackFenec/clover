#ifndef MOCKICLIENT_H_
#define MOCKICLIENT_H_
#include "gmock/gmock.h"
#include "../include/IClient.h"

class MockIClient : public IClient 
{
public:

	MOCK_METHOD1(ProcessClient, void(std::shared_ptr<IClientServer>));
	MOCK_METHOD1(Send, void(std::string message));
	MOCK_METHOD0(Start, void());
};

#endif // !IMOCKICLIENT_H_