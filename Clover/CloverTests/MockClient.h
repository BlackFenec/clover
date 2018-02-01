#ifndef MOCKCLIENT_H_
#define MOCKCLIENT_H_
#include "gmock\gmock.h"
#include "..\Clover\Client.h"

class MockClient : public Client {
public:

	MOCK_METHOD1(SendMessage, void(std::string message));
};

#endif // !MOCKCLIENT_H_