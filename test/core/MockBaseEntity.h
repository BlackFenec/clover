#ifndef MOCKBASEENTITY_H_
#define MOCKBASEENTITY_H_
#include "gmock/gmock.h"
#include "../../src/core/BaseEntity.h"

class MockBaseEntity : public BaseEntity
{
public:

	MOCK_METHOD0(GetComponents, std::list<BaseComponent*>());
	MOCK_METHOD0(GetUuid, UUID*());
};

#endif // !MOCKBASEENTITY_H_