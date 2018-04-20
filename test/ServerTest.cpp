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

TEST(ServerTest, WhenProcessClientThenClientMessageIsReceived)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, ReceiveMessage());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessClient(clientServer);
}

TEST(ServerTest, WhenProcessClientThenMessagesAreSentToClient)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, SendMessages());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessClient(clientServer);
}

TEST(ServerTest, WhenProcessClientAndClientIsClosingThenClientIsShutdown)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Shutdown());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessClient(clientServer);
}

TEST(ServerTest, WhenProcessClientAndClientIsClosingThenClientIsClose)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	std::shared_ptr<MockIClientServer> clientServer(new NiceMock<MockIClientServer>());
	ON_CALL(*clientServer, IsClosing()).WillByDefault(Return(true));
	EXPECT_CALL(*clientServer, Close());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->ProcessClient(clientServer);
}

TEST(ServerTest, WhenRunThenSocketBindingIsDone)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Bind());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenServerCreationIsDoneWithPort)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, CreateServer("27015"));

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSocketInitializationIsDone)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Initialize());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunAndIsClosingThenSocketIsClose)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Close());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSocketRunAcceptingConnection)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Accept());

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Run();
}

TEST(ServerTest, WhenRunThenSocketRunListening)
{
	std::shared_ptr<MockITcpSocket> socket(new NiceMock<MockITcpSocket>());
	ON_CALL(*socket, Accept()).WillByDefault(Return(nullptr));
	EXPECT_CALL(*socket, Listen());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Run();
}