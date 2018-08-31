#include "gtest/gtest.h"
#include "..\..\src\core\EntityManager.h"
#include "..\..\src\physic\PositionComponent.h"

class EntityManagerTest : public ::testing::Test
{
protected:

	EntityManagerTest() {}

	virtual ~EntityManagerTest() {}

	virtual void SetUp() {}

	virtual void TearDown() {}
};

TEST_F(EntityManagerTest, WhenGetEntitiesThenAllCreatedEntitiesAreReturned)
{
	Entity * entity = EntityManager::GetInstance()->CreateEntity({ new PositionComponent(1,1) });

	ASSERT_EQ(entity, EntityManager::GetInstance()->GetEntities().front());
}