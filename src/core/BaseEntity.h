#ifndef BASEENTITY_H_
#define BASEENTITY_H_

#include "BaseComponent.h"
#include "Rpc.h"
#include <list>

class BaseEntity
{
private:

	std::list<BaseComponent> m_Components;
	UUID* m_Uuid;

public:

	BaseEntity()
	{
		this->m_Components = std::list<BaseComponent>();
		UuidCreate(m_Uuid);
	};

	virtual ~BaseEntity();

	UUID* GetUuid()
	{
		return m_Uuid;
	}

};

#endif