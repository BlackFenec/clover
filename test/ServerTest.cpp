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
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	EXPECT_CALL(*socket, Close());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Close();
}

TEST(ServerTest, WhenProcessSendingClientThenClientMessageIsReceived)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, ReceiveMessage());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessSendingClient(clientServer);
}

TEST(ServerTest, WhenProcessReceivingClientThenMessagesAreSentToClient)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, SendMessages());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessReceivingClient(clientServer);
}

TEST(ServerTest, WhenProcessReceivingClientAndClientIsClosingThenClientIsShutdown)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Shutdown());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessReceivingClient(clientServer);
}

TEST(ServerTest, WhenProcessReceivingClientAndClientIsClosingThenClientIsClose)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Close());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessReceivingClient(clientServer);
}

TEST(ServerTest, WhenProcessSendingClientAndClientIsClosingThenClientIsShutdown)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Shutdown());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessSendingClient(clientServer);
}

TEST(ServerTest, WhenProcessSendingClientAndClientIsClosingThenClientIsClose)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Close());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessSendingClient(clientServer);
}

TEST(ServerTest, WhenRunThenSocketBindingIsDoneTwice)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Bind()).Times(2);

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenServerCreationIsDoneWithReceivingAndSendingPort)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, CreateServer("27015"));
	EXPECT_CALL(*socket, CreateServer("27016"));

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSocketInitializationIsDoneTwice)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Initialize()).Times(2);

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunAndIsClosingThenSocketIsClosedTwice)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Close()).Times(2);

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSocketStartAcceptingConnectionTwice)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Accept()).Times(2);

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSocketStartListeningTwice)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Listen()).Times(2);

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}