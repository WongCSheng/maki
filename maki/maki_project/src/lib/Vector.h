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
	friend gfxVector2 operator+(const gfxVector2& l, const gfxVector2& r)
	{
		gfxVector2 result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		return result;
	}
	friend gfxVector2 operator-(const gfxVector2& l, const gfxVector2& r)
	{
		gfxVector2 result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		return result;
	}
	friend gfxVector2 operator*(float l, const gfxVector2& r)
	{
		gfxVector2 result;
		result.x = l * r.x;
		result.y = l * r.y;
		return result;
	}
	friend gfxVector2 operator*(const gfxVector2& r, float l)
	{
		gfxVector2 result;
		result.x = r.x * l;
		result.y = r.y * l;
		return result;
	}

	//dot product between 2 vectors
	friend float operator*(const gfxVector2& l, const gfxVector2& r)
	{
		return (l.x * r.x + l.y * l.y);
	}


	//cross product between 2 vectors
	friend float operator^(const gfxVector2& l, const gfxVector2& r)
	{
		return (l.x * r.x - l.y * l.y);
	}

	public:
		//constructors & destructors
		gfxVector2() = default;
		gfxVector2(float x = 0, float y = 0) : x(x), y(y) {};
		gfxVector2(const gfxVector2& v = { 0,0 }) {};
		~gfxVector2();

		//operator = assignment
		gfxVector2& operator=(const gfxVector2& v)
		{
			v.x = this->x;
			v.y = this->y;
			return *this;
		}

		//[] operators, for accessing elements
		float& operator[](unsigned int i);
		const float& operator[](unsigned int i) const;

		//arithmetic vector operations
		gfxVector2& operator+=(const gfxVector2& v)
		{
			this->x += v.x;
			this->y = v.y;
			return *this;
		}
		gfxVector2& operator-=(const gfxVector2& v)
		{
			this->x -= v.x;
			this->y -= v.y;
			return *this;
		}

		//arithmetic scalar operations
		gfxVector2& operator*=(float i)
		{
			this->x *= i;
			this->y *= i;
			return *this;
		}
		gfxVector2& operator/=(float i)
		{
			this->x /= i;
			this->y /= i;
			return *this;
		}

		//arithmetic negation
		gfxVector2 operator-(void)
		{
			gfxVector2 result;
			result.x = -x;
			result.y = -y;
			return result;
		}

		//find length of vector
		float length(const gfxVector2& v) const
		{
			return sqrt(v.x * v.x + v.y * v.y);
		}

		//normalization
		void Normalize(gfxVector2& vecResult, const gfxVector2 vec)
		{
			vecResult.x = vec.x / length(vec);
			vecResult.y = vec.y / length(vec);
		}

		//delegates
		float& x; //access to X component
		float& y; //access to Y component

		private:
			//data member
			float mVec[2];

};
#endif // !VECTOR_H_
