#include "StateMachine.h"

template <class entityType>
StateMachine<entityType>::StateMachine(entityType* entity) : m_Owner(entity), m_CurrentState(nullptr)
{

}

template <class entityType>
StateMachine<entityType>::~StateMachine()
{
	delete m_State;
}

template <class entityType>
void StateMachine<entityType>::SetCurrentState(State<entityType>* state)
{
	m_CurrentState = state;
}

template <class entityType>
void StateMachine<entityType>::ChangeState(State<entityType>* newState)
{
	m_CurrentState->Exit(m_Owner);
	m_CurrentState = newState;
	m_CurrentState->Enter(m_Owner);
}

template <class entityType>
void StateMachine<entityType>::Update()
{
	m_CurrentState->Execute();
}