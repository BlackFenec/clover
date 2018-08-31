#include "gtest/gtest.h"
#include "..\..\src\physic\PhysicSystem.h"


class PhysicSystemTest : public ::testing::Test
{
protected:

	PhysicSystem * system;
	
	PhysicSystemTest() {}

	virtual ~PhysicSystemTest() {}

	virtual void SetUp()
	{
		system = new PhysicSystem();
	}

	virtual void TearDown()
	{
		delete system;
	}
};

TEST_F(PhysicSystemTest, WhenTickThenEachEntityAdvance)
{
	PositionComponent * p = new PositionComponent(2, 2);
	BaseEntity * e = new BaseEntity(std::vector<BaseComponent*>() = { p });
	
	std::vector<BaseEntity*> entities;
	entities.push_back(e);

	system->Tick(entities);

	ASSERT_EQ(Vector2D(3, 3), p->GetPosition());
}