#include "gtest/gtest.h"
#include "MockIClient.h"
#include "MockIClientServer.h"
#include "MockITcpSocket.h"
#include "../../src/network/Client.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Mock;

class ClientTest : public ::testing::Test 
{
protected:

	std::unique_ptr<IClient> m_Client;
	std::shared_ptr<MockIClientServer> m_ClientServer;
	std::shared_ptr<std::ostream> m_Output;
	std::shared_ptr<MockITcpSocket> m_Socket;

	ClientTest() {}

	virtual ~ClientTest() {}

	virtual void SetUp()
	{
		m_ClientServer = std::shared_ptr<MockIClientServer>(new NiceMock<MockIClientServer>());
		m_Socket = std::shared_ptr<MockITcpSocket>(new NiceMock<MockITcpSocket>());

		std::shared_ptr<std::ostream> output(&std::cout, [](void*) {});
		m_Output = output;

		m_Client = std::make_unique<Client>(m_Socket, m_Output);
	}

	virtual void TearDown()
	{
		m_Client.release();
		m_ClientServer.reset();
		m_Output.reset();
		m_Socket.reset();
	}
};

TEST_F(ClientTest, WhenGetClientServerThenClientServerIsGet)
{
	m_Client->SetClientServer(m_ClientServer);

	ASSERT_EQ(m_ClientServer, m_Client->GetClientServer());
}

TEST_F(ClientTest, WhenSendThenMessageIsQueue)
{
	std::string message = "mymessage";
	m_Client->SetClientServer(m_ClientServer);

	EXPECT_CALL(*m_ClientServer, QueueMessage(message));

	m_Client->Send(message);
}

TEST_F(ClientTest, WhenSendThenSocketInitializationIsDone)
{
	ON_CALL(*m_Socket, ConnectToServer()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_Socket, Initialize());

	try
	{
		m_Client->Send("mymessage");
	}
	catch (std::exception ex)
	{}
}

TEST_F(ClientTest, WhenSendThenSocketCreationIsDoneWithServerAdressAndPort)
{
	ON_CALL(*m_Socket, ConnectToServer()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_Socket, CreateClient("localhost", "27016"));

	try
	{
		m_Client->Send("mymessage");
	}
	catch (std::exception ex)
	{}
}

TEST_F(ClientTest, WhenSendThenSocketConnectWithServer)
{
	EXPECT_CALL(*m_Socket, ConnectToServer()).WillOnce(Return(nullptr));

	try
	{
		m_Client->Send("mymessage");
	}
	catch (std::exception ex)
	{}
}

TEST_F(ClientTest, WhenSendThenSocketIsntConnectWithServer)
{
	ON_CALL(*m_Socket, ConnectToServer()).WillByDefault(Return(nullptr));

	ASSERT_THROW(m_Client->Send("mymessage"); , std::exception);
}

TEST_F(ClientTest, WhenSendThenMessagesAreSend)
{
	m_Client->SetClientServer(m_ClientServer);

	EXPECT_CALL(*m_ClientServer, SendMessages());

	m_Client->Send("mymessage");
}

TEST_F(ClientTest, WhenSetClientServerThenClientServerIsSet)
{
	m_Client->SetClientServer(m_ClientServer);

	ASSERT_EQ(m_ClientServer, m_Client->GetClientServer());
}

TEST_F(ClientTest, WhenStartThenSocketIsntConnectWithServer)
{
	ON_CALL(*m_Socket, ConnectToServer()).WillByDefault(Return(nullptr));

	ASSERT_THROW(m_Client->Start(), std::exception);
}

TEST_F(ClientTest, WhenStartThenSocketConnectWithServer)
{
	EXPECT_CALL(*m_Socket, ConnectToServer()).WillOnce(Return(nullptr));

	try
	{
		m_Client->Start();
	}
	catch (std::exception ex)
	{}
}

TEST_F(ClientTest, WhenStartThenSocketCreationIsDoneWithServerAdressAndPort)
{
	ON_CALL(*m_Socket, ConnectToServer()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_Socket, CreateClient("localhost", "27015"));

	try
	{
		m_Client->Start();
	}
	catch (std::exception ex)
	{}
}

TEST_F(ClientTest, WhenStartThenSocketInitializationIsDone)
{
	ON_CALL(*m_Socket, ConnectToServer()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_Socket, Initialize());

	try
	{
		m_Client->Start();
	}
	catch (std::exception ex)
	{}
}

int main(int argc, char **argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}