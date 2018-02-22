#include "pch.h"
#include "..\Clover\Server.h"
#include <memory>
using ::testing::AtLeast;

TEST(ServerStart, SocketInitializationIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}