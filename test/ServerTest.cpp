#include "gtest/gtest.h"
#include "MockIClientServer.h"
#include "MockIServer.h"
#include "MockITcpSocket.h"
#include "../include/Server.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class ServerTest : public ::testing::Test 
{
protected:

	std::shared_ptr<MockIClientServer> m_ClientServer;
	std::shared_ptr<MockITcpSocket> m_ReceivingSocket;
	std::shared_ptr<MockITcpSocket> m_SendingSocket;
	std::unique_ptr<IServer> m_Server;

	ServerTest() {}

	virtual ~ServerTest() {}

	virtual void SetUp() 
	{
		std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
		m_ClientServer = clientServer;

		std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
		m_ReceivingSocket = receivingSocket;

		std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
		m_SendingSocket = sendingSocket;

		m_Server = std::make_unique<Server>(m_ReceivingSocket, m_SendingSocket, true);
	}

	virtual void TearDown() 
	{
		m_ClientServer = nullptr;
		m_ReceivingSocket = nullptr;
		m_SendingSocket = nullptr;
		m_Server = nullptr;
	}
};

TEST_F(ServerTest, WhenProcessSendingClientThenClientMessageIsReceived)
{
	ON_CALL(*m_ClientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*m_ClientServer, ReceiveMessage());

	m_Server->ProcessSendingClient(m_ClientServer);
}

TEST_F(ServerTest, WhenProcessReceivingClientThenMessagesAreSentToClient)
{
	ON_CALL(*m_ClientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*m_ClientServer, SendMessages());

	m_Server->ProcessReceivingClient(m_ClientServer);
}

TEST_F(ServerTest, WhenProcessReceivingClientAndClientIsClosingThenClientIsShutdown)
{
	ON_CALL(*m_ClientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*m_ClientServer, Shutdown());

	m_Server->ProcessReceivingClient(m_ClientServer);
}

TEST_F(ServerTest, WhenProcessReceivingClientAndClientIsClosingThenClientIsClose)
{
	ON_CALL(*m_ClientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*m_ClientServer, Close());

	m_Server->ProcessReceivingClient(m_ClientServer);
}

TEST_F(ServerTest, WhenProcessSendingClientAndClientIsClosingThenClientIsShutdown)
{
	ON_CALL(*m_ClientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*m_ClientServer, Shutdown());

	m_Server->ProcessSendingClient(m_ClientServer);
}

TEST_F(ServerTest, WhenProcessSendingClientAndClientIsClosingThenClientIsClose)
{
	ON_CALL(*m_ClientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*m_ClientServer, Close());

	m_Server->ProcessSendingClient(m_ClientServer);
}

TEST_F(ServerTest, WhenRunThenReceivingSocketBindingIsDone)
{
	ON_CALL(*m_ReceivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_ReceivingSocket, Bind());

	m_Server->Run();
}

TEST_F(ServerTest, WhenRunThenSendingSocketBindingIsDone)
{
	ON_CALL(*m_SendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_SendingSocket, Bind());

	m_Server->ListenSendingSockets();
}

TEST_F(ServerTest, WhenRunThenServerCreationIsDoneWithReceivingPort)
{
	ON_CALL(*m_ReceivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_ReceivingSocket, CreateServer("27015"));

	m_Server->Run();
}

TEST_F(ServerTest, WhenRunThenServerCreationIsDoneWithSendingPort)
{
	ON_CALL(*m_SendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_SendingSocket, CreateServer("27016"));

	m_Server->ListenSendingSockets();
}

TEST_F(ServerTest, WhenRunThenReceivingSocketInitializationIsDone)
{
	ON_CALL(*m_ReceivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_ReceivingSocket, Initialize());

	m_Server->Run();
}

TEST_F(ServerTest, WhenRunThenSendingSocketInitializationIsDone)
{
	ON_CALL(*m_SendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_SendingSocket, Initialize());

	m_Server->ListenSendingSockets();
}

TEST_F(ServerTest, WhenRunAndIsClosingThenReceivingSocketIsClosed)
{
	ON_CALL(*m_ReceivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_ReceivingSocket, Close());

	m_Server->Run();
}

TEST_F(ServerTest, WhenRunAndIsClosingThenSendingSocketIsClosed)
{
	ON_CALL(*m_SendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_SendingSocket, Close());

	m_Server->ListenSendingSockets();
}

TEST_F(ServerTest, WhenRunThenReceivingSocketStartAcceptingConnection)
{
	ON_CALL(*m_ReceivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_ReceivingSocket, Accept());

	m_Server->Run();
}

TEST_F(ServerTest, WhenRunThenSendingSocketStartAcceptingConnection)
{
	ON_CALL(*m_SendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_SendingSocket, Accept());

	m_Server->ListenSendingSockets();
}

TEST_F(ServerTest, WhenRunThenReceivingSocketStartListening)
{
	ON_CALL(*m_ReceivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_ReceivingSocket, Listen());

	m_Server->Run();
}

TEST_F(ServerTest, WhenRunThenSendingSocketStartListening)
{
	ON_CALL(*m_SendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*m_SendingSocket, Listen());

	m_Server->ListenSendingSockets();
}