#include "BaseEntity.h"

BaseEntity::BaseEntity()
{
	this->m_Components = std::list<BaseComponent>();
	UuidCreate(&m_Uuid);
}

BaseEntity::~BaseEntity()
{

}

UUID* BaseEntity::GetUuid()
{
	return &m_Uuid;
}