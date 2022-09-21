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
#include <glm/glm/fwd.hpp>

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */

class gfxMatrix3
	// a 3x3 matrix class. Because we're doing a 2D game we dont have to do 4x4
	// column major
{
	public:
		gfxMatrix3(float a00 = 0, float a10 = 0, float a20 = 0, float a01 = 0, float a11 = 0, float a21 = 0, float a02 = 0, float a12 = 0, float a22 = 0);
		gfxMatrix3(const float m[9]);
		gfxMatrix3(const gfxMatrix3& rhs);

		// set to identity matrix
		void setIdentity();
		void swap(float& x, float& y);
		// flip matrix
		void Transpose();
		// set all elements to 0
		void setZero();

		gfxMatrix3 getTranspose(gfxMatrix3 m) const;

		gfxMatrix3 getInverse() const;
		
		//rotate by a certain degree in x/y direction
		void SetRotation(float degree, float x_Axis, float y_Axis);
		//scaling by x/y
		void SetScale(float sx, float sy);
		//translate by x/y
		void SetTranslation(float tx, float ty);
		
		// matrix calculations
		gfxMatrix3 operator*(const gfxMatrix3& rhs) const;
		gfxVector2 operator*(const gfxVector2& rhs) const;
		gfxMatrix3 operator*(float value) const;
		gfxMatrix3 operator+(const gfxMatrix3& rhs) const;
		gfxMatrix3& operator=(const gfxMatrix3& rhs);

		float a[9];

};

#endif // MATRIX_H_