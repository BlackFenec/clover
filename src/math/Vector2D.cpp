#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : x(0.0), y(0.0)
{}

Vector2D::Vector2D(double x, double y) : x(x), y(y)
{}

Vector2D::~Vector2D()
{}

Vector2D Vector2D::operator+(const Vector2D &lhs, const Vector2D &rhs)
{
	return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D &lhs, const Vector2D &rhs)
{
	return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2D Vector2D::operator*(const Vector2D &lhs, double rhs)
{
	return Vector2D(lhs.x * rhs, lhs.y * rhs);
}

Vector2D Vector2D::operator/(const Vector2D &lhs, double rhs)
{
	return Vector2D(lhs.x / rhs, lhs.y / rhs);
}

double Vector2D::Length()
{
	return sqrt(pow(lhs.x,2) + pow(lhs.y,2));
}

double Vector2D::Length(const Vector2D & v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void Vector2D::Normalize()
{
	double length = this->Length();
	this.x /= length;
	this.y /= length;
}

Vector2D Vector2D::Normalize(const Vector2D &v)
{
	Vector2D normalizedVector(v);
	double length = Length(v);
	normalizedVector.x /= length;
	normalizedVector.y /= length;

	return normalizedVector;
}