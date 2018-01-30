#include "pch.h"

TEST(ServerStart, TrueIsReturned) {
	Server * s = new Server();
	EXPECT_TRUE(s->Start());
}