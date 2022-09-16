#ifndef MATRIX_4F_H
#define MATRIX_4F_H

#include "mymath.h"
#include <math.h>
#include "Vector3.h"

#pragma warning( disable: 4290 ) 

class Matrix4f
{
public:
	Matrix4f(float a00 = 0, float a10 = 0, float a20 = 0, float a30 = 0, float a01 = 0, float a11 = 0, float a21 = 0, float a31 = 0, float a02 = 0, float a12 = 0, float a22 = 0, float a32 = 0, float a03 = 0, float a13 = 0, float a23 = 0, float a33 = 0);
	Matrix4f(const float m[16]);
	Matrix4f(const Matrix4f &rhs);
	void SetToIdentity(void);
	void Transpose(void);
	void SetToZero(void);
	Matrix4f GetTranspose() const;
	Matrix4f GetInverse() const throw( DivideByZero );
	Matrix4f operator*(const Matrix4f& rhs) const;
	Matrix4f operator+(const Matrix4f& rhs) const;
	Matrix4f& operator=(const Matrix4f& rhs);
	Matrix4f operator*(float scalar) const;
	Vector3 operator*(const Vector3& rhs) const;
	void SetToRotation(float degrees, float axisX, float axisY, float axisZ) throw( DivideByZero );
	void SetToScale(float sx, float sy, float sz);
	void SetToTranslation(float tx, float ty, float tz);
	void SetToFrustum(double left, double right, double	bottom, double top, double near, double far);
	void SetToLookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ);
	void SetToPerspective(double fovy, double aspect, double zNear, double zFar);
	void SetToOrtho(double left, double right, double bottom, double top, double nearVal, double farVal);

	float a[16];
};

#endif //MTX_44_H
