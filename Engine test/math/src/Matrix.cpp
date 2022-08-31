/******************************************************************************/
/*!
\file		Matrix.cpp
\author 	Wong Chong Sheng
\par    	email: w.chongsheng\@digipen.edu
\date   	March 18, 2022
\brief		This file contains functions for Mtx33 matrix type.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Matrix.h"
#include <math.h>
#include <limits>

#define PI			3.14159265358f

namespace CSD1130
{
	//Non-default constructor of matrix
	Matrix::Matrix(const float* pArr) :
		m00{ pArr[0] }, m01{ pArr[1] }, m02{ pArr[2] },
		m10{ pArr[3] }, m11{ pArr[4] }, m12{ pArr[5] },
		m20{ pArr[6] }, m21{ pArr[7] }, m22{ pArr[8] }
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] = *(pArr + i);
		}
	}

	//Non-default contructor of matrix
	Matrix::Matrix(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22) : m00{ _00 }, m01{ _01 }, m02{ _02 }, m10{ _10 }, m11{ _11 }, m12{ _12 }, m20{ _20 }, m21{ _21 }, m22{ _22 }
	{
	}

	//Overloaded = operator for matrix
	Matrix& Matrix::operator=(const Matrix& rhs)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] = rhs.m[i];
		}

		return *this;
	}

	//Overloaded *= operator for matrix
	Matrix& Matrix::operator *= (const Matrix& rhs)
	{
		return *this = *this * rhs;
	}

	//Overloaded * operator for matrix
	Matrix operator * (const Matrix& lhs, const Matrix& rhs)
	{
		Matrix tempmat;

		tempmat.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20;
		tempmat.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21;
		tempmat.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22;

		tempmat.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20;
		tempmat.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21;
		tempmat.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22;

		tempmat.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20;
		tempmat.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21;
		tempmat.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22;

		return tempmat;
	}

	//Returns vector after multiplying by matrix
	Vector2D  operator * (const Matrix& pMtx, const Vector2D& rhs)
	{
		Vector2D tempvec;

		tempvec.x = rhs.x * pMtx.m00 + rhs.y * pMtx.m01 + 1 * pMtx.m02;
		tempvec.y = rhs.x * pMtx.m10 + rhs.y * pMtx.m11 + 1 * pMtx.m12;

		return tempvec;
	}

	//Returns matrix identity
	void Mtx33Identity(Matrix& pResult)
	{
		for (int i = 0; i < 9; i++)
		{
			pResult.m[i] = 0;
		}

		pResult.m00 = 1;
		pResult.m11 = 1;
		pResult.m22 = 1;
	}

	//Returns matrix translation
	void Mtx33Translate(Matrix& pResult, float x, float y)
	{
		Mtx33Identity(pResult);

		pResult.m00 = 1;
		pResult.m11 = 1;
		pResult.m22 = 1;
		pResult.m02 = x;
		pResult.m12 = y;
	}

	//Returns matrix scale
	void Mtx33Scale(Matrix& pResult, float x, float y)
	{
		Mtx33Identity(pResult);

		pResult.m00 = x;
		pResult.m11 = y;
	}

	//Returns Rotation matrix in radians
	void Mtx33RotRad(Matrix& pResult, float angle)
	{
		Mtx33Identity(pResult);

		pResult.m00 = cos(angle);
		pResult.m01 = -sin(angle);
		pResult.m10 = sin(angle);
		pResult.m11 = cos(angle);
	}

	//Returns Rotation matrix in degrees
	void Mtx33RotDeg(Matrix& pResult, float angle)
	{
		float degree = angle * (PI / 180);

		for (int i = 0; i < 9; i++)
		{
			pResult.m[i] = 0;
		}

		pResult.m00 = cos(degree);
		pResult.m01 = -sin(degree);
		pResult.m10 = sin(degree);
		pResult.m11 = cos(degree);
		pResult.m22 = 1;
	}

	//Returns transpose matrix
	void Mtx33Transpose(Matrix& pResult, const Matrix& pMtx)
	{
		pResult.m00 = pMtx.m00;
		pResult.m01 = pMtx.m10;
		pResult.m02 = pMtx.m20;
		pResult.m10 = pMtx.m01;
		pResult.m11 = pMtx.m11;
		pResult.m12 = pMtx.m21;
		pResult.m20 = pMtx.m02;
		pResult.m21 = pMtx.m12;
		pResult.m22 = pMtx.m22;
	}

	//Returns Inverse matrix
	void Mtx33Inverse(Matrix* pResult, float* determinant, const Matrix& pMtx)
	{
		*determinant = (pMtx.m00 * (pMtx.m11 * pMtx.m22 - pMtx.m21 * pMtx.m12))
			- (pMtx.m01 * (pMtx.m10 * pMtx.m22 - pMtx.m20 * pMtx.m12))
			+ (pMtx.m02 * (pMtx.m10 * pMtx.m21 - pMtx.m20 * pMtx.m11));

		if (*determinant < FLT_EPSILON && *determinant > FLT_EPSILON)
		{
			*pResult = nullptr;
			return;
		}

		float InvDet = 1 / *determinant;
		Mtx33 temp(0, 0, 0, 0, 0, 0, 0, 0, 0);

		temp.m00 = (pMtx.m11 * pMtx.m22 - pMtx.m21 * pMtx.m12) * InvDet;
		temp.m01 = (pMtx.m10 * pMtx.m22 - pMtx.m20 * pMtx.m12) * InvDet;
		temp.m02 = (pMtx.m10 * pMtx.m21 - pMtx.m20 * pMtx.m11) * InvDet;

		temp.m10 = (pMtx.m01 * pMtx.m22 - pMtx.m21 * pMtx.m02) * InvDet;
		temp.m11 = (pMtx.m00 * pMtx.m22 - pMtx.m20 * pMtx.m02) * InvDet;
		temp.m12 = (pMtx.m00 * pMtx.m21 - pMtx.m20 * pMtx.m01) * InvDet;

		temp.m20 = (pMtx.m01 * pMtx.m12 - pMtx.m11 * pMtx.m02) * InvDet;
		temp.m21 = (pMtx.m00 * pMtx.m12 - pMtx.m10 * pMtx.m02) * InvDet;
		temp.m22 = (pMtx.m00 * pMtx.m11 - pMtx.m10 * pMtx.m01) * InvDet;

		*pResult = temp;
	}
}