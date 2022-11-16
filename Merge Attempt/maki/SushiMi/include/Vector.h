/*!
@file    Vector.h
@author	 Louis Wang

Vector header file for all vector calculations
*//*__________________________________________________________________________*/

#ifndef VECTOR_H_
#define VECTOR_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Headers/STL_Header.h"

/*                                                                    classes
----------------------------------------------------------------------------- */
class gfxVector2
{

public:
	//constructors & destructors
	gfxVector2() : x(), y() {};
	gfxVector2(float x, float y) : x(x), y(y)
	{
	};
	gfxVector2(const gfxVector2& v) : x(v.x), y(v.y) {};
	~gfxVector2() { /*delete[] &mVec[2];*/ };

	gfxVector2(gfxVector2&&) = default;
	//operator = assignment
	gfxVector2& operator=(const gfxVector2& v)
	{
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
	/*need operator to access elements???
	* ------------------------------------------
	//[] operators, for accessing elements
	float& operator[](unsigned int i)
	{
		if (i > 2 || i < 0)
		{
			std::cout << "Array out of bounds";

			//return first array 0
			return mVec[0];
		}
		else
		{
			return mVec[i];
		}
	}
	const float& operator[](unsigned int i) const
	{
			if (i > 2)
			{
				std::cout << "Array out of bounds";

				//return first array 0
				return mVec[0];
			}
			else
			{
				return mVec[i];
			}
	}
	*/
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
		return (l.x * r.x + l.y * r.y);
	}


	//cross product between 2 vectors
	friend float operator^(const gfxVector2& l, const gfxVector2& r)
	{
		return (l.x * r.x - l.y * r.y);
	}

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
		this->x = -x;
		this->y = -y;
		return *this;
	}

	//find length of vector
	float length(const gfxVector2& v) const
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	//normalization
	float Normalize(gfxVector2& vecResult, const gfxVector2 vec)
	{
		vecResult.x = vec.x / length(vec);
		vecResult.y = vec.y / length(vec);
	}

	//delegates
	float x; //access to X component
	float y; //access to Y component

private:
	//data member
	float mVec[2]{};

};
#endif // !VECTOR_H_