#include "gtest/gtest.h"
#include "..\..\src\messaging\NewPositionContent.h"

class NewPositionContentTest : public ::testing::Test
{
protected:

	NewPositionContentTest() {}

	virtual ~NewPositionContentTest() {}

	virtual void SetUp()
	{}

	virtual void TearDown()
	{}
};

TEST_F(NewPositionContentTest, WheGetPositionThenPositionIsReturned)
{
	PositionComponent * expected = new PositionComponent();
	NewPositionContent n(expected);

	ASSERT_EQ(expected, n.GetPosition());
}