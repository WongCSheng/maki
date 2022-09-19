#include "../include/Matrix.h"

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

