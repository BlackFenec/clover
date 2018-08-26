#ifndef BASEENTITY_H_
#define BASEENTITY_H_

#include "BaseComponent.h"
#include "Rpc.h"
#include <vector>

class BaseEntity
{
private:

	std::vector<BaseComponent*> m_Components;
	GUID m_Guid;

public:

	BaseEntity();
	BaseEntity(std::vector<BaseComponent*> components);
	virtual ~BaseEntity();

	std::vector<BaseComponent*> GetComponents();
	GUID GetGuid();
};

#endif