#include "pch.h"
#include "..\Clover\Server.h"
#include <memory>
using ::testing::AtLeast;
using ::testing::Return;

TEST(ServerStart, SocketInitializationIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketCreationIsDoneWithPort) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CreateServer("27015"));

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketBindIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Bind());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketStartListening) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Listen());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketStartAcceptingConnection) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Accept());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, MessageIsReceivedFromClientWhenConnectionAccepted) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, ReceiveFromClient());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, MessageReceivedFromClientIsSentBack) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	ON_CALL(*socket, ReceiveFromClient()).WillByDefault(Return(message));
	EXPECT_CALL(*socket, SendToClient(message));

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, ClientIsShutdownAfterSendingBackMessage) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, ShutdownClient());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, ClientIsCloseAfterShutdown) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CloseClient());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerClose, SocketIsClose) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Close());

	std::unique_ptr<IServer> s(new Server(socket));
	s->Close();
}