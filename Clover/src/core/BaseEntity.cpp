#include "BaseEntity.h"

BaseEntity::BaseEntity()
{
	CoCreateGuid(&m_Guid);
}

BaseEntity::BaseEntity(std::vector<BaseComponent*> components)
{
	this->m_Components = components;
	for (std::vector<BaseComponent*>::iterator it = this->m_Components.begin(); it != this->m_Components.end(); ++it)
	{
		(*it)->owner = this;
	}
	CoCreateGuid(&m_Guid);
}

BaseEntity::~BaseEntity()
{
	for (std::vector<BaseComponent*>::iterator it = this->m_Components.begin(); it != this->m_Components.end(); ++it)
		delete (*it);
}

std::vector<BaseComponent*> BaseEntity::GetComponents()
{
	return m_Components;
}

GUID BaseEntity::GetGuid()
{
	return m_Guid;
}