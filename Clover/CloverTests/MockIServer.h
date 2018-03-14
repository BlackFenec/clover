#ifndef MOCKISERVER_H_
#define MOCKISERVER_H_
#include "gmock\gmock.h"
#include "..\Clover\IServer.h"

class MockIServer : public IServer {
public:

	MOCK_METHOD0(Start, void());
	MOCK_METHOD0(Close, void());
};

#endif // !MOCKISERVER_H_