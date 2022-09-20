#include "../include/Matrix.h"
#include <glm/glm/matrix.hpp>

gfxMatrix3::gfxMatrix3(float a00, float a10, float a20, float a01, float a11, float a21, float a02, float a12, float a22)
{
	a[0] = a00;
	a[1] = a10;
	a[2] = a20;
	a[3] = a01;
	a[4] = a11;
	a[5] = a21;
	a[6] = a02;
	a[7] = a12;
	a[8] = a22;
}

gfxMatrix3::gfxMatrix3(const float m[9])
{
	for (int i = 0; i < 9; i++)
	{
		a[i] = m[i];
	}
}

gfxMatrix3::gfxMatrix3(const gfxMatrix3& rhs)
{
	for (int i = 0; i < 9; i++)
	{
		a[i] = rhs.a[i];
	}
}

void gfxMatrix3::setIdentity()
{
	// set all elements to 0
	setZero();
	// set [0][0],[1][1] and [2][2] to 1
	a[0] = a[4] = a[8] = 1;
}
//swap x and y elements
void gfxMatrix3::swap(float& x, float& y)
{
	float temp = x;
	x = y;
	y = temp;
}

//transpose the matrix(flipping) ( Have to test to see if it works)
void gfxMatrix3::Transpose()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			swap(a[i * 3 + j], a[(j * 3 + i)]);
		}
	}
}

// set all elements to 0 by looping thru the elements
void gfxMatrix3::setZero()
{
	for (int i = 0; i < 9; i++)
	{
		a[i] = 0;
	}
}

gfxMatrix3 gfxMatrix3::getTranspose() const
{
	gfxMatrix3 mtx(*this);
	mtx.Transpose();
	return mtx;
}
//do later have to write out
gfxMatrix3 gfxMatrix3::getInverse() const
{
	
}

void gfxMatrix3::SetRotation(float degree, float x_Axis, float y_Axis)
{

}

void gfxMatrix3::SetScale(float sx, float sy)
{

}

void gfxMatrix3::SetTranslation(float tx, float ty)
{

}

gfxMatrix3 gfxMatrix3::operator*(const gfxMatrix3& rhs) const
{

}
gfxVector2 gfxMatrix3::operator*(const gfxVector2& rhs) const
{

}
gfxMatrix3 gfxMatrix3::operator*(float value) const
{
	gfxMatrix3 temp;
	for (int i = 0; i < 9; i++)
	{
		temp.a[i] = a[i] * value;
	}

	return temp;
}
gfxMatrix3 gfxMatrix3::operator+(const gfxMatrix3& rhs) const
{
	return(
		a[0] + rhs.a[0],
		a[1] + rhs.a[1],
		a[2] + rhs.a[2],
		a[3] + rhs.a[3],
		a[4] + rhs.a[4],
		a[5] + rhs.a[5],
		a[6] + rhs.a[6],
		a[7] + rhs.a[7],
		a[8] + rhs.a[8]
		);
}
gfxMatrix3& gfxMatrix3::operator=(const gfxMatrix3& rhs)
{
	for (int i = 0; i < 9; i++)
	{
		a[i] = rhs.a[i];
	}
	return *this;
}