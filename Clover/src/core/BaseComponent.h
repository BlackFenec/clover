#ifndef BASECOMPONENT_H_
#define BASECOMPONENT_H_

class BaseEntity;

class BaseComponent {

public :
	BaseEntity* owner;

	BaseComponent();
	virtual ~BaseComponent() {};
};
#endif