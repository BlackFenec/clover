#include "gtest/gtest.h"
#include "MockIClient.h"
#include "MockITcpSocket.h"
#include "../include/Client.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::Return;

class ClientTest : public ::testing::Test {
protected:
	ClientTest() {}

	virtual ~ClientTest() {}

	virtual void SetUp(){}

	virtual void TearDown(){}
};

TEST(ClientTest, WhenClientSendMessageThenEmptyMessageIsNotSentToSocket)
{
	std::string message;
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Send(message)).Times(0);

	//std::unique_ptr<IClient> c(new Client(socket));
	//std::string response = c->Send(message);
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientSendMessageThenSocketIsClose)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Close());

	/*std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send("my message");*/
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientSendMessageThenSocketIsShutdown)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Shutdown());

	/*std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send("my message");*/
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientSendMessageThenSocketReceiveResponse)
{
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Receive()).WillOnce(Return(message));

	/*std::unique_ptr<IClient> c(new Client(socket));
	std::string response = c->Send(message);
	ASSERT_EQ(response, message);*/
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientSendMessageThenValidMessageIsSentToSocket)
{
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Send(message));

	/*std::unique_ptr<IClient> c(new Client(socket));
	c->Send(message);*/
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientStartThenSocketConnectWithServer)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, ConnectToServer());

	/*std::unique_ptr<IClient> c(new Client(socket));
	c->Start();*/
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientStartThenSocketCreationIsDoneWithServerAdressAndPort)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CreateClient("localhost", "27015"));

	/*std::unique_ptr<IClient> c(new Client(socket));
	c->Start();*/
	EXPECT_FALSE(TRUE);
}

TEST(ClientTest, WhenClientStartThenSocketInitializationIsDone)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize());

	/*std::unique_ptr<IClient> c(new Client(socket));
	c->Start();*/
	EXPECT_FALSE(TRUE);
}

int main(int argc, char **argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}