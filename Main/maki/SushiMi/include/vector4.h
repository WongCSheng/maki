#pragma once
/*!
@file    Vector.h
@author	 Louis Wang

Vector header file for all vector calculations
*//*__________________________________________________________________________*/

#ifndef VECTOR4_H_
#define VECTOR4_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Headers/STL_Header.h"

/*                                                                    classes
----------------------------------------------------------------------------- */
class gfxVector4
{

public:
	//constructors & destructors
	gfxVector4() : x(), y(),z(), w() {};
	gfxVector4(float x, float y, float z, float w) : x(x), y(y),z(z), w(w)
	{
	};
	gfxVector4(const gfxVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
	~gfxVector4() { /*delete[] &mVec[2];*/ };

	gfxVector4(gfxVector4&&) = default;
	//operator = assignment
	gfxVector4& operator=(const gfxVector4& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->w = v.w;
		this->z = v.z;
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
	friend gfxVector4 operator+(const gfxVector4& l, const gfxVector4& r)
	{
		gfxVector4 result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
		result.z = l.z + r.z;
		result.w = l.w + r.w;
		return result;
	}
	friend gfxVector4 operator-(const gfxVector4& l, const gfxVector4& r)
	{
		gfxVector4 result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
		result.z = l.z - r.z;
		result.w = l.w - r.w;
		return result;
	}
	friend gfxVector4 operator*(float l, const gfxVector4& r)
	{
		gfxVector4 result;
		result.x = l * r.x;
		result.y = l * r.y;
		result.z = l * r.z;
		result.w = l * r.w;
		return result;
	}
	friend gfxVector4 operator*(const gfxVector4& r, float l)
	{
		gfxVector4 result;
		result.x = r.x * l;
		result.y = r.y * l;
		result.z = r.z * l;
		result.w = r.w * l;
		return result;
	}

	//dot product between 2 vectors
	friend float operator*(const gfxVector4& l, const gfxVector4& r)
	{
		return (l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w);
	}


	//arithmetic vector operations
	gfxVector4& operator+=(const gfxVector4& v)
	{
		this->x += v.x;
		this->y += v.y;
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
	void Normalize(gfxVector2& vecResult, const gfxVector2 vec)
	{
		vecResult.x = vec.x / length(vec);
		vecResult.y = vec.y / length(vec);
	}

	//delegates
	float x; //access to X component
	float y; //access to Y component
	float z; //access to Z component
	float w; //access to W component

private:
	//data member
	double mVec[4]{};

};
#endif // !VECTOR_H_