#include "Vector3.h"


Vector3::Vector3() :
x(0),
y(0),
z(0)
{
}

Vector3::Vector3(float x, float y, float z) :
x(x),
y(y),
z(z)
{

}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator-(void) const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator=(const Vector3 &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3 &vec) const
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3 &vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3& Vector3::operator+=(const Vector3 &vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3 &vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3 Vector3::operator*(const float scalar) const 
{
	return Vector3(scalar * x, scalar * y, scalar * z);
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

void Vector3::Set(const Vector3 &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

void Vector3::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::SetZero()
{
	x = y = z = 0;
}

float Vector3::Length(void) const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::LengthSquared(void) const
{
	return x * x + y * y + z * z;
}

float Vector3::Dot(const Vector3& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::Cross(const Vector3& vec) const
{
	return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

Vector3 Vector3::Normalized(void) const throw(DivideByZero)
{
	float d = Length();
	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		throw DivideByZero();
	return Vector3(x / d, y / d, z / d);
}

Vector3& Vector3::Normalize(void) throw(DivideByZero)
{
	float d = Length();
	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		throw DivideByZero();
	x /= d;
	y /= d;
	z /= d;
	return *this;
}

Vector3 Vector3::Zero()
{
	return Vector3();
}

Vector3 Vector3::Splat(float splat)
{
	return Vector3(splat, splat, splat);
}

#include <sstream>

std::string Vector3::ToString(void)
{
	std::ostringstream ss;
	ss << x << ", " << y << ", " << z;
	return ss.str();
}