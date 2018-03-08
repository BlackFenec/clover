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

TEST(ClientSendMessage, SocketReceiveResponse) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Send(message)).Times(1);
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
	std::string serverAdress = "localhost";
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, CreateClient(serverAdress, serverPort)).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}

TEST(ClientStart, SocketConnectWithServer) {
	std::string serverAdress = "localhost";
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, CreateClient(serverAdress, serverPort)).Times(1);
	EXPECT_CALL(*socket, ConnectToServer()).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->Start();
}

TEST(ClientClose, SocketIsClose) {
	std::string serverAdress = "localhost";
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Close()).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->Close();
}