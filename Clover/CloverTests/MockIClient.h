#ifndef MOCKICLIENT_H_
#define MOCKICLIENT_H_
#include "gmock\gmock.h"
#include "..\Clover\IClient.h"

class MockIClient : public IClient 
{
public:

	MOCK_METHOD1(Send, std::string(std::string message));
	MOCK_METHOD0(Start, void());
};

#endif // !IMOCKICLIENT_H_