#include "BaseEntity.h"

BaseEntity::BaseEntity()
{
	this->m_Components = std::list<BaseComponent*>();
	//UuidCreate(&m_Uuid);
}

BaseEntity::BaseEntity(std::list<BaseComponent*> components)
{
	this->m_Components = components;
	for (std::list<BaseComponent*>::iterator it = this->m_Components.begin(); it != this->m_Components.end(); ++it)
	{
		(*it)->owner = this;
	}
	//UuidCreate(&m_Uuid);
}

BaseEntity::~BaseEntity()
{
	for (std::list<BaseComponent*>::reverse_iterator it = this->m_Components.rbegin(); it != this->m_Components.rend(); ++it)
		delete (*it);
}

std::list<BaseComponent*> BaseEntity::GetComponents()
{
	return m_Components;
}

UUID* BaseEntity::GetUuid()
{
	return &m_Uuid;
}