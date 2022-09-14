/*!
@file    Matrix.h
@author	 Louis Wang

Matrix header file for all matrix calculations
*//*__________________________________________________________________________*/

#ifndef MATRIX_H_
#define MATRIX_H_

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "Vector.h"
#include "Math.h"
#include "Headers.h"

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */

class gfxMatrix3
	// a 3x3 matrix class. Because we're doing a 2D game we dont have to do 4x4
{
	// matrix multiplication
	friend gfxMatrix3 operator*(const gfxMatrix3& l, const gfxMatrix3& r)
	{
		return l * r;
	}
	
	//scalar multiplication
	friend gfxMatrix3 operator*(float l, const gfxMatrix3& r)
	{
		
	}
};

#endif // MATRIX_H_