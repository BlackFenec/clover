#include "gtest/gtest.h"
#include "MockIServer.h"
#include "MockITcpSocket.h"
#include "../include/Server.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::Return;

class ServerTest : public ::testing::Test {
protected:
	ServerTest() {}

	virtual ~ServerTest() {}

	virtual void SetUp() {}

	virtual void TearDown() {}
};

//TEST(ServerTest, WhenServerCloseThenSocketIsClose)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, Close());
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Close();
//}
//
//TEST(ServerTest, WhenServerStartThenSocketBindIsDone)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, Bind());
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//}
//
//TEST(ServerTest, WhenServerStartThenMessageIsReceivedFromClientWhenConnectionAccepted)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	std::shared_ptr<SOCKET> client = nullptr;
//
//	ON_CALL(*socket, Accept()).WillByDefault(Return(client));
//	//EXPECT_CALL(*socket, ReceiveFrom(client));
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//	EXPECT_FALSE(TRUE);
//}
//
//TEST(ServerTest, WhenServerStartThenMessageReceivedFromClientIsSentBack)
//{
//	std::string message = "my message";
//	std::shared_ptr<SOCKET> client = nullptr;
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//
//	ON_CALL(*socket, Accept()).WillByDefault(Return(client));
//	//ON_CALL(*socket, ReceiveFrom(client)).WillByDefault(Return(message));
//	//EXPECT_CALL(*socket, SendTo(message, client));
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//	EXPECT_FALSE(TRUE);
//}
//
//TEST(ServerTest, WhenServerStartThenSocketCreationIsDoneWithPort)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, CreateServer("27015"));
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//}
//
//TEST(ServerTest, WhenServerStartThenSocketInitializationIsDone)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, Initialize());
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//}
//
//TEST(ServerTest, WhenServerStartThenSocketIsClose)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, Close());
//
//	std::unique_ptr<IServer> s(new Server(socket, true));
//	s->Start();
//}
//
//TEST(ServerTest, WhenServerStartThenSocketStartAcceptingConnection)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, Accept());
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//}
//
//TEST(ServerTest, WhenServerStartThenSocketStartListening)
//{
//	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
//	EXPECT_CALL(*socket, Listen());
//
//	std::unique_ptr<IServer> s(new Server(socket,true));
//	s->Start();
//}