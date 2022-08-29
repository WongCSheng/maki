/******************************************************************************/
/*!
\file		Vector.cpp
\author 	Wong Chong Sheng
\par    	email: w.chongsheng\@digipen.edu
\date   	March 18, 2022
\brief		This file defines the functions of Vector type.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Vector.h"
#include <math.h>

namespace Vector
{
	//Non-default constructor for vector
	Vector::Vector(float _x, float _y) : x{ _x }, y{ _y }
	{
	}

	//Overloaded += operator for vector
	Vector& Vector::operator += (const Vector& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	//Overloaded -= operator for vector
	Vector& Vector::operator -= (const Vector& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	//Overloaded *= operator for vector
	Vector& Vector::operator *= (float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	//Overloaded /= operator for vector
	Vector& Vector::operator /= (float rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	//Overloaded unary operator for vector
	Vector Vector::operator -() const
	{
		Vector tempvec{ -x, -y };

		return tempvec;
	}

	//Overloaded + operator for vector
	Vector operator+(const Vector& lhs, const Vector& rhs)
	{
		Vector tempvector;

		tempvector.x = lhs.x + rhs.x;
		tempvector.y = lhs.y + rhs.y;

		return tempvector;
	}

	//Overloaded - operator for vector
	Vector operator-(const Vector& lhs, const Vector& rhs)
	{
		Vector tempvector;

		tempvector.x = lhs.x - rhs.x;
		tempvector.y = lhs.y - rhs.y;

		return tempvector;
	}

	//Overloaded * operator for vector
	Vector operator*(const Vector& lhs, float rhs)
	{
		Vector tempvector;

		tempvector.x = lhs.x * rhs;
		tempvector.y = lhs.y * rhs;

		return tempvector;
	}

	//Overloaded * operator for vector
	Vector operator*(float lhs, const Vector& rhs)
	{
		Vector tempvector;

		tempvector.x = lhs * rhs.x;
		tempvector.y = lhs * rhs.y;

		return tempvector;
	}

	//Overloaded / operator for vector
	Vector operator/(const Vector& lhs, float rhs)
	{
		Vector tempvector;

		tempvector.x = lhs.x / rhs;
		tempvector.y = lhs.y / rhs;

		return tempvector;
	}

	//Overloaded -= operator for vector
	void VectorNormalize(Vector& pResult, const Vector& pVec0)
	{
		pResult = pVec0 / VectorLength(pVec0);
	}

	//Returns length of vector
	float VectorLength(const Vector& pVec0)
	{
		float length;

		length = VectorDotProduct(pVec0, pVec0);

		return sqrt(length);
	}

	//Returns length squared
	float VectorSquareLength(const Vector& pVec0)
	{
		float SquareLength;

		SquareLength = VectorDotProduct(pVec0, pVec0);

		return SquareLength;
	}

	//Returns distance between 2 points, also known as vector
	float VectorDistance(const Vector& pVec0, const Vector& pVec1)
	{
		float distance;

		distance = ((pVec1.x - pVec0.x) * (pVec1.x - pVec0.x)) + ((pVec1.y - pVec0.y) * (pVec1.y - pVec0.y));

		distance = sqrt(distance);

		return distance;
	}

	//Returns distance between 2 points squared
	float VectorSquareDistance(const Vector& pVec0, const Vector& pVec1)
	{
		float distance;

		distance = ((pVec1.x - pVec0.x) * (pVec1.x - pVec0.x)) + ((pVec1.y - pVec0.y) * (pVec1.y - pVec0.y));

		return distance;
	}

	//Returns dot product of 2 vectors
	float VectorDotProduct(const Vector& pVec0, const Vector& pVec1)
	{
		float dotprod;

		dotprod = (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);

		return dotprod;
	}

	//Returns magnitude of cross product of 2 vectors
	float VectorCrossProductMag(const Vector& pVec0, const Vector& pVec1)
	{
		float CrossProductMag;
		Vector Cross;

		Cross.x = pVec1.y * pVec0.x;
		Cross.y = pVec1.x * pVec0.y;

		CrossProductMag = Cross.x - Cross.y;

		return CrossProductMag;
	}
}