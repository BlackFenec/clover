#include "gtest/gtest.h"
#include "..\..\src\physic\Vector2D.h"

class Vector2DTest : public ::testing::Test
{
protected:
	
	Vector2DTest() {}

	virtual ~Vector2DTest() {}

	virtual void SetUp()
	{
		
	}

	virtual void TearDown()
	{
		
	}
};

TEST_F(Vector2DTest, WhenAddingTwoVectorsThenCoordinatesOfBothVectorsAreAdded)
{
	Vector2D first(2, 2), second(4,3), expected(6,5);
	
	ASSERT_EQ(expected, first + second);
}

TEST_F(Vector2DTest, WhenSubtractingTwoVectorsThenCoordinatesOfSecondVectorAreSubtractedFromFirstVector)
{
	Vector2D first(10, 10), second(4, 3), expected(6, 7);

	ASSERT_EQ(expected, first - second);
}

TEST_F(Vector2DTest, WhenMultiplyingVectorThenVectorCoordinatesAreMultiplied)
{
	Vector2D v(2, 3), expected(4, 6);
	double factor = 2;

	ASSERT_EQ(expected, v * factor);
}

TEST_F(Vector2DTest, WhenDividingVectorThenVectorCoordinatesAreDivided)
{
	Vector2D v(10, 8), expected(5, 4);
	double divider = 2;

	ASSERT_EQ(expected, v / divider);
}

TEST_F(Vector2DTest, WhenDotProductThenRespectivesCoordinatesAreMultipliedAndAdded)
{
	Vector2D first(3, 2), second(4, 3);
	double expected = 18;

	ASSERT_EQ(expected, first.DotProduct(second));
}

TEST_F(Vector2DTest, WhenDotProductWithPerpendicularVectorThenResultIsZero)
{
	Vector2D first(4, 0), second(0, 4);
	double expected = 0;

	ASSERT_EQ(expected, first.DotProduct(second));
}

TEST_F(Vector2DTest, WhenNormalizeThenVectorCoordinatesAreDividedByItsLength)
{
	Vector2D v(4, 3), expected(0.8, 0.6);

	ASSERT_EQ(expected, v.Normalize(v));
}

TEST_F(Vector2DTest, WhenNormalizeWithVectorThenVectorCoordinatesAreDividedByItsLength)
{
	Vector2D v(4, 3), expected(0.8,0.6);

	v.Normalize();

	ASSERT_EQ(expected,v);
}

TEST_F(Vector2DTest, WhenLengthThenSquareRootOfBothCoordinatesPowerAddedIsDone)
{
	Vector2D v(4, 3);
	double expected = 5;

	ASSERT_EQ(expected, v.Length());
}

TEST_F(Vector2DTest, WhenLengthWithVectorThenSquareRootOfBothCoordinatesPowerAddedIsDone)
{
	Vector2D v(4, 3);
	double expected = 5;

	ASSERT_EQ(expected, v.Length(v));
}