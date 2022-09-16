#ifndef VECTOR3_H
#define VECTOR3_H

#include "mymath.h"
#include <string>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	float x, y, z;

	Vector3& operator=(const Vector3 &vec);

	Vector3 operator-(void) const;
	Vector3 operator+(const Vector3 &vec) const;
	Vector3 operator-(const Vector3 &vec) const;
	Vector3& operator+=(const Vector3 &vec);
	Vector3 operator-=(const Vector3 &vec);
	Vector3 operator*(const float scalar) const;
	Vector3& operator*=(float scalar);

	void Set(const Vector3 &vec);
	void Set(float x, float y, float z);
	void SetZero();

	float Length(void) const;
	float LengthSquared(void) const;
	float Dot(const Vector3 &vec) const;
	Vector3 Cross(const Vector3 &vec) const;
	Vector3 Normalized(void) const throw (DivideByZero);
	Vector3& Normalize(void) throw (DivideByZero);

	std::string ToString(void);

	static Vector3 Zero();
	static Vector3 Splat(float splat);
};

#endif