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

TEST(ServerStart, SocketCreationIsDoneWithPort) {
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, Create(serverPort)).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketBindIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, Create("27015")).Times(1);
	EXPECT_CALL(*socket, Bind()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}