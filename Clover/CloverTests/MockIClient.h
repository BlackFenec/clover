#ifndef MOCKICLIENT_H_
#define MOCKICLIENT_H_
#include "gmock\gmock.h"
#include "..\Clover\IClient.h"

class MockIClient : public IClient {
public:

	MOCK_METHOD1(SendMessage, void(std::string message));
};

#endif // !IMOCKICLIENT_H_