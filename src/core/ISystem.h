#ifndef ISYSTEM_H_
#define ISYSTEM_H_

#include "BaseEntity.h"

class ISystem {
public :

	ISystem() {};
	virtual ~ISystem() {};

	virtual void Tick(std::list<BaseEntity*> entities) = 0;
};
#endif