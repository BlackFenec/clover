#include "gtest/gtest.h"
#include "..\..\src\physic\PositionComponent.h"
#include "..\..\src\physic\Vector2D.h"

class PositionComponentTest : public ::testing::Test
{
protected:
	
	PositionComponentTest() {}

	virtual ~PositionComponentTest() {}

	virtual void SetUp()
	{
		
	}

	virtual void TearDown()
	{
		
	}
};

TEST_F(PositionComponentTest, WhenGetPositionThenPositionVectorIsReturned)
{
	PositionComponent p(2,2);
	Vector2D expected(2, 2);
	
	ASSERT_EQ(expected, p.GetPosition());
}

TEST_F(PositionComponentTest, WhenAddThenVectorParameterIsAddedToVector)
{
	PositionComponent expected(4, 3), actual(2, 2);
	actual.Add(Vector2D(2, 1));

	ASSERT_EQ(expected, actual);
}