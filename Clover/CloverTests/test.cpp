#include "pch.h"

TEST(ServerReturnTruth, TrueIsReturned) {
	Server * s = new Server();
	EXPECT_TRUE(s->returntruth());
}