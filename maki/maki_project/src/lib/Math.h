/*!
@file    Math.h
@author	 Louis Wang

Maths functions like min max, special value like PI and deg->rad conversions
*//*__________________________________________________________________________*/

#ifndef MATH_H_
#define MATH_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Headers.h"

/*                                                                  constants
----------------------------------------------------------------------------- */

const float PI				= 4.0f * std::atan(1.0f);
const float DEG_TO_RAD		= PI / 180.0f;
const float RAD_TO_DEG		= 180.0f / PI;

/*                                                                  functions
----------------------------------------------------------------------------- */
//finding the min between 2 elements
template<typename T_>
inline T_ min(const T_& l, const T_& r)
{
	return(l < r ? l : r);
}

//finding the min between 2 elements
template<typename T_>
inline T_ min(const T_& l, const T_& r)
{
	return(l < r ? l : r);
}

//finding the max between 2 elements
template<typename T_>
inline T_ max(const T_& l, const T_& r)
{
	return(l > r ? l : r);
}

//convert degree to radians
inline float deg2rad(float d)
{
	return (d * DEG_TO_RAD);
}

//convert radians to deg
inline float rad2deg(float r)
{
	return (r * RAD_TO_DEG);
}
#endif // !MATH_H_
