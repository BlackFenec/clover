#include "pch.h"
#include "..\Clover\Client.h"
#include <memory>
using ::testing::AtLeast;
using ::testing::Return;

TEST(ClientSendMessage, ValidMessageIsSentToSocket) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Send(message)).Times(1);

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
	EXPECT_CALL(*socket, Close()).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send("my message");
}

TEST(ClientSendMessage, SocketIsShutdown) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Shutdown()).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send("my message");
}

TEST(ClientSendMessage, SocketReceiveResponse) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Receive()).Times(1).WillOnce(Return(message));

	std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send(message);
	ASSERT_EQ(response, message);
}

TEST(ClientStart, SocketInitializationIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}

TEST(ClientStart, SocketCreationIsDoneWithServerAdressAndPort) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CreateClient("localhost", "27015")).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}

TEST(ClientStart, SocketConnectWithServer) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, ConnectToServer()).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}