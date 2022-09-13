/*!
@file    Vector.h
@author	 Louis Wang

Vector header file for all vector calculations
*//*__________________________________________________________________________*/

#ifndef VECTOR_H_
#define VECTOR_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Headers.h"

/*                                                                    classes
----------------------------------------------------------------------------- */
class gfxVector2
{
	//arithmetic operators
	friend gfxVector2 operator+(const gfxVector2& l, const gfxVector2& r);
	friend gfxVector2 operator-(const gfxVector2& l, const gfxVector2& r);
	friend gfxVector2 operator*(float l, const gfxVector2& r);

	//dot product between 2 vectors
	friend float operator*(const gfxVector2& l, const gfxVector2& r);

	//cross product between 2 vectors
	friend gfxVector2 operator^(const gfxVector2& l, const gfxVector2& r);

	public:
		//constructors & destructors
		gfxVector2();
		gfxVector2(float x, float y);
		gfxVector2(const gfxVector2& v);
		~gfxVector2();

		//operator = assignment
		gfxVector2& operator=(const gfxVector2& v);

		//[] operators, for accessing elements
		float& operator[](unsigned int i);
		const float& operator[](unsigned int i) const;

		//arithmetic vector operations
		gfxVector2& operator+=(const gfxVector2& v);
		gfxVector2& operator-=(const gfxVector2& v);

		//arithmetic scalar operations
		gfxVector2& operator*=(float i);
		gfxVector2& operator/=(float i);

		//arithmetic negation
		gfxVector2 operator-(void);

		//find length of vector
		float length() const;

		//normalization
		gfxVector2 Norm() const;
		void Normalize();

		//reinitialization
		void ResetTo(float x, float y);

		//delegates
		float& x; //access to X component
		float& y; //access to Y component

		private:
			//data member
			float mVec[2];

};
#endif // !VECTOR_H_
