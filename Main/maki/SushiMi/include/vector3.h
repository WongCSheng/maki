/*!
@file    Vector3.h
@author	 Louis Wang

Vector header file for all vector3 calculations 
*//*__________________________________________________________________________*/

#ifndef VECTOR3_H_
#define VECTOR3_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Headers/STL_Header.h"

/*                                                                    classes
----------------------------------------------------------------------------- */
class gfxVector3
{

public:
	//constructors & destructors
	gfxVector3() : x(), y(), z() {};
	gfxVector3(float x, float y, float z) : x(x), y(y), z(z)
	{
	};
	gfxVector3(const gfxVector3& v) : x(v.x), y(v.y),z(v.z) {};
	~gfxVector3() { delete[] & mVec; };

	//operator = assignment
	gfxVector3& operator=(const gfxVector3& v)
	{
		this->x = v.x;
		this->y = v.y;
        this->z = v.z;
		return *this;
	}
	//arithmetic operators
	friend gfxVector3 operator+(const gfxVector3& l, const gfxVector3& r)
	{
		gfxVector3 result;
		result.x = l.x + r.x;
		result.y = l.y + r.y;
        result.z = l.z + r.z;
		return result;
	}
	friend gfxVector3 operator-(const gfxVector3& l, const gfxVector3& r)
	{
		gfxVector3 result;
		result.x = l.x - r.x;
		result.y = l.y - r.y;
        result.z = l.z - r.z;
		return result;
	}
	friend gfxVector3 operator*(float l, const gfxVector3& r)
	{
		gfxVector3 result;
		result.x = l * r.x;
		result.y = l * r.y;
        result.z = l * r.z;
		return result;
	}
	friend gfxVector3 operator*(const gfxVector3& r, float l)
	{
		gfxVector3 result;
		result.x = r.x * l;
		result.y = r.y * l;
        result.z = r.z * l;
		return result;
	}

	//dot product between 2 vectors
	friend float operator*(const gfxVector3& l, const gfxVector3& r)
	{
		return (l.x * r.x + l.y * r.y + l.z * r.z);
	}


	//cross product between 2 vectors
	friend float operator^(const gfxVector3& l, const gfxVector3& r)
	{
		return (l.x * r.x - l.y * r.y - l.z * r.z);
	}

	//arithmetic vector operations
	gfxVector3& operator+=(const gfxVector3& v)
	{
		this->x += v.x;
<<<<<<< HEAD
		this->y = v.y;
        this->z = v.z;
=======
		this->y += v.y;
        this->z += v.z;
>>>>>>> M3-submission-branch
		return *this;
	}
	gfxVector3& operator-=(const gfxVector3& v)
	{
		this->x -= v.x;
		this->y -= v.y;
<<<<<<< HEAD
        this->z = v.z;
=======
        this->z -= v.z;
>>>>>>> M3-submission-branch
		return *this;
	}

	//arithmetic scalar operations
	gfxVector3& operator*=(float i)
	{
		this->x *= i;
		this->y *= i;
        this->z *= i;
		return *this;
	}
	gfxVector3& operator/=(float i)
	{
		this->x /= i;
		this->y /= i;
        this->z /= i;
		return *this;
	}

	//arithmetic negation
	gfxVector3 operator-(void)
	{
		this->x = -x;
		this->y = -y;
        this->z = -z;
		return *this;
	}

	//find length of vector
	float length(const gfxVector3& v) const
	{
		return sqrt(v.x * v.x + v.y * v.y - v.z * v.z);
	}

	//normalization
	void Normalize(gfxVector3& vecResult, const gfxVector3 vec)
	{
		vecResult.x = vec.x / length(vec);
		vecResult.y = vec.y / length(vec);
        vecResult.z = vec.z / length(vec);
	}

	//delegates
	float x; //access to X component
	float y; //access to Y component
    float z; //access to Z component

private:
	//data member
	float mVec[3]{};

};
#endif // !VECTOR_H_