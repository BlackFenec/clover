#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : x(0.0), y(0.0)
{}

Vector2D::Vector2D(double x, double y) : x(x), y(y)
{}

Vector2D::~Vector2D()
{}

Vector2D Vector2D::operator+(const Vector2D &v)
{
	return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D &v)
{
	return Vector2D(this->x + - v.x, this->y - v.y);
}

Vector2D Vector2D::operator*(const double &rhs)
{
	return Vector2D(this->x * rhs, this->y * rhs);
}

Vector2D Vector2D::operator/(const double &rhs)
{
	return Vector2D(this->x / rhs, this->y / rhs);
}

double Vector2D::Length()
{
	return sqrt(pow(this->x,2) + pow(this->y,2));
}

double Vector2D::Length(const Vector2D & v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void Vector2D::Normalize()
{
	double length = this->Length();
	this->x /= length;
	this->y /= length;
}

Vector2D Vector2D::Normalize(const Vector2D &v)
{
	Vector2D normalizedVector(v);
	double length = Length(v);
	normalizedVector.x /= length;
	normalizedVector.y /= length;

	return normalizedVector;
}

double Vector2D::DotProduct(const Vector2D &v)
{
	return this->x * v.x + this->y * v.y;
}