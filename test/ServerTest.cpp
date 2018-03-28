#include "gtest/gtest.h"
#include "MockIServer.h"
#include "MockITcpSocket.h"
#include "../include/Server.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::Return;

TEST(ServerClose, SocketIsClose) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Close());

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Close();
}

TEST(ServerStart, ClientIsCloseAfterShutdown) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	std::shared_ptr<SOCKET> client = nullptr;

	ON_CALL(*socket, Accept()).WillByDefault(Return(client));
	EXPECT_CALL(*socket, CloseClient(client));

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, ClientIsShutdownAfterSendingBackMessage)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	std::shared_ptr<SOCKET> client = nullptr;

	ON_CALL(*socket, Accept()).WillByDefault(Return(client));
	EXPECT_CALL(*socket, ShutdownClient(client));

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, SocketBindIsDone) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Bind());

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, MessageIsReceivedFromClientWhenConnectionAccepted) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	std::shared_ptr<SOCKET> client = nullptr;

	ON_CALL(*socket, Accept()).WillByDefault(Return(client));
	EXPECT_CALL(*socket, ReceiveFromClient(client));

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, MessageReceivedFromClientIsSentBack) 
{
	std::string message = "my message";
	std::shared_ptr<SOCKET> client = nullptr;
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());

	ON_CALL(*socket, Accept()).WillByDefault(Return(client));
	ON_CALL(*socket, ReceiveFromClient(client)).WillByDefault(Return(message));
	EXPECT_CALL(*socket, SendToClient(message, client));

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, SocketCreationIsDoneWithPort) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CreateServer("27015"));

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, SocketInitializationIsDone) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize());

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, SocketIsClose)
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Close());

	std::unique_ptr<IServer> s(new Server(socket, true));
	s->Start();
}

TEST(ServerStart, SocketStartAcceptingConnection) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Accept());

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}

TEST(ServerStart, SocketStartListening) 
{
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Listen());

	std::unique_ptr<IServer> s(new Server(socket,true));
	s->Start();
}