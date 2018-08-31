#include "gtest/gtest.h"
#include "..\..\src\core\Engine.h"
#include <chrono>
#include <thread>

class EngineTest : public ::testing::Test
{
protected:

	Engine * engine;

	EngineTest() {}

	virtual ~EngineTest() {}

	virtual void SetUp()
	{
		engine = new Engine();
	}

	virtual void TearDown()
	{
		delete engine;
	}
};

TEST_F(EngineTest, WhenCurrentStateThenCurrentEngineStateIsReturned)
{
	ASSERT_EQ(EngineState::stopped, engine->CurrentState());
}

TEST_F(EngineTest, WhenStopThenCurrentEngineStateIsStopped)
{
	engine->Stop();

	ASSERT_EQ(EngineState::stopped, engine->CurrentState());
}