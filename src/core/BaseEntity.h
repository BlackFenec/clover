#ifndef ENTITY_H_
#define ENTITY_H_

#include "BaseComponent.h"
#include "Rpc.h"
#include <list>

class BaseEntity
{
private:

	std::list<BaseComponent> m_Components;
	UUID m_Uuid;

public:

	BaseEntity()
	{
		this->m_Components = new std::list<BaseComponent>();
		UuidCreate(&m_Uuid);
	};

	UUID GetUuid()
	{
		return m_Uuid;
	}

	virtual ~BaseEntity();
};

#endif