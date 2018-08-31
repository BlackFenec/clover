#include "gtest/gtest.h"
#include "..\..\src\core\BaseEntity.h"
#include "..\..\src\messaging\Message.h"
#include "..\..\src\messaging\MessageContent.h"
#include "..\..\src\messaging\MessageType.h"

class MessageTest : public ::testing::Test
{
protected:
	
	MessageTest() {}

	virtual ~MessageTest() {}

	virtual void SetUp()
	{}

	virtual void TearDown()
	{}
};

TEST_F(MessageTest, WheGetSourceThenBaseEntitySourceIsReturned)
{
	BaseEntity * expected = new BaseEntity();
	Message m(expected, nullptr, MessageType::NewPosition, nullptr);

	ASSERT_EQ(expected, m.GetSource());
	delete expected;
}

TEST_F(MessageTest, WheGetTargetThenBaseEntityTargetIsReturned)
{
	BaseEntity * expected = new BaseEntity();
	Message m(nullptr, expected, MessageType::NewPosition, nullptr);

	ASSERT_EQ(expected, m.GetTarget());
	delete expected;
}

TEST_F(MessageTest, WheGetTypeThenMessageTypeIsReturned)
{
	MessageType expected = MessageType::Talking;
	Message m(nullptr, nullptr, expected, nullptr);

	ASSERT_EQ(expected, m.GetType());
}

TEST_F(MessageTest, WheGetContentThenMessageContentIsReturned)
{
	MessageContent * expected = new MessageContent();
	Message m(nullptr, nullptr, MessageType::NewPosition, expected);

	ASSERT_EQ(expected, m.GetContent());
}