#ifndef STATE_H_
#define STATE_H_

template <class entityType>
class State
{
private :
	State() {};

public:
	virtual ~State() {};

	virtual void Enter(entityType*) = 0;
	virtual void Execute(entityType*) = 0;
	virtual void Exit(entityType*) = 0;
};

#endif