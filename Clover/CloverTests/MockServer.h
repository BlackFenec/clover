#ifndef MOCKSERVER_H_
#define MOCKSERVER_H_
#include "gmock\gmock.h"
#include "..\Clover\Server.h"

class MockServer : public Server {
public:

	MOCK_METHOD0(Start, bool());
};

#endif // !MOCKSERVER_H_