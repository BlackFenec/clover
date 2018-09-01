#include "gtest\gtest.h"
#include "..\..\src\core\BaseEntity.h"
#include "..\..\src\physic\PositionComponent.h"


class BaseEntityTest : public ::testing::Test
{
protected:
	
	BaseEntity * entity;

	BaseEntityTest() {}

	virtual ~BaseEntityTest() {}

	virtual void SetUp()
	{
		entity = new BaseEntity();
	}

	virtual void TearDown()
	{
		delete entity;
	}
};

TEST_F(BaseEntityTest, WhenGetComponentsThenEntityComponentsAreReturned)
{
	PositionComponent * p = new PositionComponent(2, 2);
	BaseEntity * e = new BaseEntity(std::vector<BaseComponent*>() = { p });

	ASSERT_EQ(p, e->GetComponents().front());
}