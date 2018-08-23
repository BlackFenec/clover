#include "gtest/gtest.h"
#include "../../src/physic/PhysicSystem.h"
#include "../core/MockBaseEntity.h"

using ::testing::NiceMock;

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

TEST_F(PhysicSystemTest, WhenTickThenComponentsOfEachEntityAreGet)
{
	NiceMock<MockBaseEntity> * e = new NiceMock<MockBaseEntity>();
	
	EXPECT_CALL(*e, GetComponents());
	std::list<BaseEntity*> entities;
	entities.push_back(e);

	system->Tick(entities);

	delete e;
}