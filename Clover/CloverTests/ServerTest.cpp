#include "pch.h"
#include "..\Clover\Server.h"
#include <memory>
using ::testing::AtLeast;

TEST(ServerStart, SocketInitializationIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketCreationIsDoneWithPort) {
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, CreateServer(serverPort)).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketBindIsDone) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, CreateServer("27015")).Times(1);
	EXPECT_CALL(*socket, Bind()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketStartListening) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, CreateServer("27015")).Times(1);
	EXPECT_CALL(*socket, Bind()).Times(1);
	EXPECT_CALL(*socket, Listen()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerStart, SocketStartAcceptingConnection) {
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, Initialize()).Times(1);
	EXPECT_CALL(*socket, CreateServer("27015")).Times(1);
	EXPECT_CALL(*socket, Bind()).Times(1);
	EXPECT_CALL(*socket, Listen()).Times(1);
	EXPECT_CALL(*socket, Accept()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Start();
}

TEST(ServerClose, SocketIsClose) {
	std::string serverAdress = "localhost";
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CloseClient()).Times(1);
	EXPECT_CALL(*socket, Close()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Close();
}

TEST(ServerClose, ClientSocketIsClose) {
	std::string serverAdress = "localhost";
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CloseClient()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->Close();
}

TEST(ServerCloseClient, ClientSocketIsClose) {
	std::string serverAdress = "localhost";
	std::string serverPort = "27015";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, CloseClient()).Times(1);

	std::unique_ptr<IServer> s(new Server(socket));
	s->CloseClient();
}