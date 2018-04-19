#include "gtest/gtest.h"
#include "MockIClient.h"
#include "MockIClientServer.h"
#include "MockITcpSocket.h"
#include "../include/Client.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class ClientTest : public ::testing::Test {
protected:
	ClientTest() {}

	virtual ~ClientTest() {}

	virtual void SetUp(){}

	virtual void TearDown(){}
};

TEST(ClientTest, WhenGetClientServerThenClientServerIsGet)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
	std::unique_ptr<IClient> c(new Client(socket, output));

	c->SetClientServer(clientServer);

	ASSERT_EQ(clientServer, c->GetClientServer());
}

TEST(ClientTest, WhenSendThenMessageIsQueue)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
	std::unique_ptr<IClient> c(new Client(socket, output));
	std::string message = "mymessage";
	c->SetClientServer(clientServer);

	EXPECT_CALL(*clientServer, QueueMessage(message));

	c->Send(message);
}

TEST(ClientTest, WhenSendThenMessagesAreSend)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
	std::unique_ptr<IClient> c(new Client(socket, output));
	c->SetClientServer(clientServer);

	EXPECT_CALL(*clientServer, SendMessages());

	c->Send("mymessage");
}

TEST(ClientTest, WhenSetClientServerThenClientServerIsSet)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
	std::unique_ptr<IClient> c(new Client(socket, output));

	c->SetClientServer(clientServer);

	ASSERT_EQ(clientServer, c->GetClientServer());
}

TEST(ClientTest, WhenStartThenSocketIsntConnectWithServer)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
	ON_CALL(*socket, ConnectToServer()).WillByDefault(Return(nullptr));

	std::unique_ptr<IClient> c(new Client(socket, output));

	ASSERT_THROW(c->Start(), std::exception);
}

TEST(ClientTest, WhenStartThenSocketConnectWithServer)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
	EXPECT_CALL(*socket, ConnectToServer()).WillOnce(Return(nullptr));

	std::unique_ptr<IClient> c(new Client(socket, output));

	try
	{
		c->Start();
	}
	catch (std::exception ex)
	{}
}

TEST(ClientTest, WhenStartThenSocketCreationIsDoneWithServerAdressAndPort)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});

	ON_CALL(*socket, ConnectToServer()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, CreateClient("localhost", "27015"));

	std::unique_ptr<IClient> c(new Client(socket, output));
	try
	{
		c->Start();
	}
	catch (std::exception ex)
	{}
}

TEST(ClientTest, WhenStartThenSocketInitializationIsDone)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});

	ON_CALL(*socket, ConnectToServer()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Initialize());

	std::unique_ptr<IClient> c(new Client(socket, output));
	try
	{
		c->Start();
	}
	catch (std::exception ex)
	{}
}

int main(int argc, char **argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}