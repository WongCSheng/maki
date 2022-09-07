/*THis is for all maths calculations*/
#include <maths.h>

using namespace mathlib;

template <typename T> max(T a, T b)
{
	return (a > b) ? T a : T b;
}

template <typename T> min(T a, T b)
{
	return (a < b) ? T a : T b;
}

template <typename T> add(T a, T b)
{
	return T a + T b;
}

template <typename T> subtract(T a, T b)
{
	return T a - T b;
}