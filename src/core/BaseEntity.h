#ifndef ENTITY_H_
#define ENTITY_H_

#include "BaseComponent.h"
#include <list>

class BaseEntity
{
private:

	std::list<BaseComponent> components;

public:

	BaseEntity()
	{
		this->components = new std::list<BaseComponent>();
	};

	
};

#endif