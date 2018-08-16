#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>

class Vector2D
{
private :
	double x;
	double y;

public :
	Vector2D();
	Vector2D(double x, double y);
	virtual ~Vector2D();

	Vector2D operator+(const Vector2D &v);
	Vector2D operator-(const Vector2D &v);
	Vector2D operator*(const double &factor);
	Vector2D operator/(const double &divider); 
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v)
	{
		os << "X: " << v.x;
		os << " Y: " << v.y;
		return os;
	}

	double DotProduct(const Vector2D &v);

	double Length();
	double Length(const Vector2D &v);

	void Normalize();
	Vector2D Normalize(const Vector2D &v);

	
};

#endif