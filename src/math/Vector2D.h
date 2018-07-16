#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class Vector2D
{
private :
	double x;
	double y;

public :
	Vector2D();
	Vector2D(double x, double y);
	virtual ~Vector2D();

	Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);
	Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);
	Vector2D operator*(const Vector2D &lhs, double rhs);
	Vector2D operator/(const Vector2D &lhs, double rhs);

	double Length();
	double Length(const Vector2D &v);

	void Normalize();
	Vector2D Normalize(const Vector2D &v);
};

#endif