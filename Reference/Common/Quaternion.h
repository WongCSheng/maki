#ifndef QUATERNION_H
#define QUATERNION_H

#include "Matrix4f.h"
#include "Vector3.h"

class Quaternion
{
public:
	float w;
	Vector3 v;

	Quaternion(void);
	Quaternion(float a, const Vector3& n) throw(DivideByZero);
	~Quaternion(void);

	const Quaternion Inverted() const;
	const Quaternion operator*(const Quaternion& q) const;
	const Vector3 operator*(const Vector3& V) const;

	float length(void) const;
	Quaternion normalized(void) const throw(DivideByZero);
	Quaternion& Normalize(void) throw(DivideByZero);

	// convert Quaternion to matrix
	Matrix4f convertTomat4(void);
	const Quaternion Slerp(const Quaternion& other, float t) const;
	void ToAxisAngle(Vector3& vecAxis, float& flAngle) const;
};

#endif

