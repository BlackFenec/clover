#include "gtest/gtest.h"
#include "..\..\src\messaging\TalkingContent.h"

class TalkingContentTest : public ::testing::Test
{
protected:

	TalkingContentTest() {}

	virtual ~TalkingContentTest() {}

	virtual void SetUp()
	{}

	virtual void TearDown()
	{}
};

TEST_F(TalkingContentTest, WheGetMessageThenMessageIsReturned)
{
	std::string expected = "hello";
	TalkingContent t(expected);

	ASSERT_EQ(expected, t.GetMessage());
}