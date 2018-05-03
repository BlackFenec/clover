#include "gtest/gtest.h"
#include "MockIClientServer.h"
#include "MockIServer.h"
#include "MockITcpSocket.h"
#include "../include/Server.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

class ServerTest : public ::testing::Test {
protected:
	ServerTest() {}

	virtual ~ServerTest() {}

	virtual void SetUp() {}

	virtual void TearDown() {}
};

TEST(ServerTest, WhenCloseThenSocketIsClose)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	EXPECT_CALL(*receivingSocket, Close());
	EXPECT_CALL(*sendingSocket, Close());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Close();
}

TEST(ServerTest, WhenProcessSendingClientThenClientMessageIsReceived)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, ReceiveMessage());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->ProcessSendingClient(clientServer);
}

TEST(ServerTest, WhenProcessReceivingClientThenMessagesAreSentToClient)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, SendMessages());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->ProcessReceivingClient(clientServer);
}

TEST(ServerTest, WhenProcessReceivingClientAndClientIsClosingThenClientIsShutdown)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Shutdown());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->ProcessReceivingClient(clientServer);
}

TEST(ServerTest, WhenProcessReceivingClientAndClientIsClosingThenClientIsClose)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Close());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->ProcessReceivingClient(clientServer);
}

TEST(ServerTest, WhenProcessSendingClientAndClientIsClosingThenClientIsShutdown)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Shutdown());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->ProcessSendingClient(clientServer);
}

TEST(ServerTest, WhenProcessSendingClientAndClientIsClosingThenClientIsClose)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Close());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->ProcessSendingClient(clientServer);
}

TEST(ServerTest, WhenRunThenReceivingSocketBindingIsDone)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*receivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*receivingSocket, Bind());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSendingSocketBindingIsDone)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*sendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*sendingSocket, Bind());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenServerCreationIsDoneWithReceivingPort)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*receivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*receivingSocket, CreateServer("27015"));

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenServerCreationIsDoneWithSendingPort)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*sendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*sendingSocket, CreateServer("27016"));

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenReceivingSocketInitializationIsDone)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*receivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*receivingSocket, Initialize());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSendingSocketInitializationIsDone)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*sendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*sendingSocket, Initialize());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunAndIsClosingThenReceivingSocketIsClosed)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*receivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*receivingSocket, Close());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunAndIsClosingThenSendingSocketIsClosed)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*sendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*sendingSocket, Close());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenReceivingSocketStartAcceptingConnection)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*receivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*receivingSocket, Accept());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSendingSocketStartAcceptingConnection)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*sendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*sendingSocket, Accept());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenReceivingSocketStartListening)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*receivingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*receivingSocket, Listen());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSendingSocketStartListening)
{
	std::shared_ptr<MockITcpSocket> receivingSocket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockITcpSocket> sendingSocket(new NiceMock<MockITcpSocket>());
	ON_CALL(*sendingSocket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*sendingSocket, Listen());

	std::unique_ptr<IServer> s(new Server(receivingSocket, sendingSocket, true));
	s->Run();
}