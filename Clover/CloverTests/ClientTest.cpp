#include "pch.h"
#include "..\Clover\Client.h"
#include <memory>
using ::testing::AtLeast;

TEST(ClientSendMessage, SocketSentMessage) {
	std::string message = "my message";
	std::shared_ptr<MockITcpSocket> socket(new MockITcpSocket());
	EXPECT_CALL(*socket, SendMessage(message)).Times(1);

	std::unique_ptr<IClient> c(new Client(socket));
	c->SendMessage(message);
}