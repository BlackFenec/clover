#include "pch.h"
#include "..\Clover\Client.h"
#include <memory>
using ::testing::AtLeast;
using ::testing::Return;

TEST(ClientSendMessage, ValidMessageIsSentToSocket) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Send(message));

	std::unique_ptr<IClient> c(new Client(socket));
	c->Send(message);
}

TEST(ClientSendMessage, EmptyMessageIsNotSentToSocket) {
	std::string message;
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Send(message)).Times(0);

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send(message);
}

TEST(ClientSendMessage, SocketIsClose) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Close());

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send("my message");
}

TEST(ClientSendMessage, SocketIsShutdown) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Shutdown());

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send("my message");
}

TEST(ClientSendMessage, SocketReceiveResponse) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Receive()).WillOnce(Return(message));

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send(message);
	ASSERT_EQ(response, message);
}

TEST(ClientStart, SocketInitializationIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize());

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}

TEST(ClientStart, SocketCreationIsDoneWithServerAdressAndPort) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CreateClient("localhost", "27015"));

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}

TEST(ClientStart, SocketConnectWithServer) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, ConnectToServer());

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}