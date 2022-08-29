/******************************************************************************/
/*!
\file		Vector.h
\author 	DigiPen
\par    	email: digipen\@digipen.edu
\date   	January 01, 20xx
\brief

Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef VECTOR_H_
#define VECTOR_H_

namespace Vector
{
#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif

/**************************************************************************/
/*!

 */
 /**************************************************************************/
	typedef union Vector
	{
		struct
		{
			float x, y;
		};

		float m[2];

		// Constructors
		Vector() {};
		Vector(float _x, float _y);

		// Assignment operators
		Vector& operator += (const Vector& rhs);
		Vector& operator -= (const Vector& rhs);
		Vector& operator *= (float rhs);
		Vector& operator /= (float rhs);

		// Unary operators
		Vector operator -() const;

	} Vector, Vec2, Point2D, Pt2;


#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( default : 4201 )
#endif

// Binary operators
	Vector operator + (const Vector& lhs, const Vector& rhs);
	Vector operator - (const Vector& lhs, const Vector& rhs);
	Vector operator * (const Vector& lhs, float rhs);
	Vector operator * (float lhs, const Vector& rhs);
	Vector operator / (const Vector& lhs, float rhs);

	/**************************************************************************/
	/*!
		In this function, pResult will be the unit vector of pVec0
	 */
	 /**************************************************************************/
	void	VectorNormalize(Vector& pResult, const Vector& pVec0);

	/**************************************************************************/
	/*!
		This function returns the length of the vector pVec0
	 */
	 /**************************************************************************/
	float	VectorLength(const Vector& pVec0);

	/**************************************************************************/
	/*!
		This function returns the square of pVec0's length. Avoid the square root
	 */
	 /**************************************************************************/
	float	VectorSquareLength(const Vector& pVec0);

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The distance between these 2 2D points is returned
	 */
	 /**************************************************************************/
	float	VectorDistance(const Vector& pVec0, const Vector& pVec1);

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The squared distance between these 2 2D points is returned.
		Avoid the square root
	 */
	 /**************************************************************************/
	float	VectorSquareDistance(const Vector& pVec0, const Vector& pVec1);

	/**************************************************************************/
	/*!
		This function returns the dot product between pVec0 and pVec1
	 */
	 /**************************************************************************/
	float	VectorDotProduct(const Vector& pVec0, const Vector& pVec1);

	/**************************************************************************/
	/*!
		This function returns the cross product magnitude
		between pVec0 and pVec1
	 */
	 /**************************************************************************/
	float	VectorCrossProductMag(const Vector& pVec0, const Vector& pVec1);
}

#endif // CSD1130_Vector_H_