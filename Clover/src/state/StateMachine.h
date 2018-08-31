#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "State.h"

template <class entityType>
class StateMachine
{
private:
	entityType * m_Owner;
	State<entityType>* m_CurrentState;

public :
	StateMachine(entityType* owner);
	virtual ~StateMachine();

	void SetCurrentState(State<entityType>* state);

	void ChangeState(State<entityType>* newState);

	void Update();
};

#endif