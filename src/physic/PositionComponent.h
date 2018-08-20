#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "..\core\BaseComponent.h"
#include "Vector2D.h"

class PositionComponent : public BaseComponent
{
private:
	Vector2D m_Position;

public :
	PositionComponent();
	PositionComponent(double x, double y);
	virtual ~PositionComponent();

	bool operator==(const PositionComponent &v) const;
	Vector2D GetPosition() const;
	void Add(Vector2D v);
};

#endif