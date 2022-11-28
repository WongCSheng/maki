/******************************************************************************/
/*!
\file		Collision.h
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\date   	2/8/2022
\brief		This source file contains the function declarations for
			building line segment, checking for collision between line segment
			and circle instances, and lastly the response when collision occurs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Matrix3x3.h"
#include "Vector2D.h"
#ifndef CSD1130_COLLISION_H_
#define CSD1130_COLLISION_H_


/******************************************************************************/
/*!
	Struct for line segment
 */
/******************************************************************************/
struct LineSegment
{
	CSD1130::Vec2	m_pt0;
	CSD1130::Vec2	m_pt1;
	CSD1130::Vec2	m_normal;
};

void BuildLineSegment(LineSegment &lineSegment,								//Line segment reference - input
					  const CSD1130::Vec2 &pos,									//position - input
					  float scale,											//scale - input
					  float dir);											//direction - input

/******************************************************************************/
/*!
 */
/******************************************************************************/
struct Circle
{
	CSD1130::Vec2  m_center;
	float	m_radius;

	// Extra credits
	float   m_mass{ 1.0f };
};

struct Ray
{
	CSD1130::Vec2	m_pt0;
	CSD1130::Vec2	m_dir;
};


// INTERSECTION FUNCTIONS
int CollisionIntersection_CircleLineSegment(const Circle &circle,			//Circle data - input
	const CSD1130::Vec2 &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	CSD1130::Vec2 &interPt,														//Intersection point - output
	CSD1130::Vec2 &normalAtCollision,												//Normal vector at collision time - output
	float &interTime,														//Intersection time ti - output
	bool & checkLineEdges);													//The last parameter is new - for Extra Credits: true = check collision with line segment edges

// Extra credits
int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const Circle &circle,													//Circle data - input
	const CSD1130::Vec2 &ptEnd,													//End circle position - input
	const LineSegment &lineSeg,												//Line segment - input
	CSD1130::Vec2 &interPt,														//Intersection point - output
	CSD1130::Vec2 &normalAtCollision,												//Normal vector at collision time - output
	float &interTime);														//Intersection time ti - output


// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
// In the case of "dynamic circle vs static pillar", velB will be 0.0f
int CollisionIntersection_CircleCircle(const Circle &circleA,				//CircleA data - input
	const CSD1130::Vec2 &velA,														//CircleA velocity - input
	const Circle &circleB,													//CircleB data - input
	const CSD1130::Vec2 &velB,														//CircleA velocity - input
	CSD1130::Vec2 &interPtA,														//Intersection point of CircleA at collision time - output
	CSD1130::Vec2 &interPtB,														//Intersection point of CircleB at collision time - output
	float &interTime);														//intersection time - output

// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
// this is a helper function to be used inside "CollisionIntersection_CircleCircle" function
// it is checking collision a moving dot vs a static circle
int CollisionIntersection_RayCircle(const Ray &ray,							//A ray containing the data of the moving dot - input
	const Circle &circle,													//Static circle data - input
	float &interTime);														//Intersection time - output






// RESPONSE FUNCTIONS
void CollisionResponse_CircleLineSegment(const CSD1130::Vec2 &ptInter,				//Intersection position of the circle - input
	const CSD1130::Vec2 &normal,													//Normal vector of reflection on collision time - input
	CSD1130::Vec2 &ptEnd,															//Final position of the circle after reflection - output
	CSD1130::Vec2 &reflected);														//Normalized reflection vector direction - output

void CollisionResponse_CirclePillar(const CSD1130::Vec2 &normal,					//Normal vector of reflection on collision time - input
	const float &interTime,													//Intersection time - input
	const CSD1130::Vec2 &ptStart,													//Starting position of the circle - input
	const CSD1130::Vec2 &ptInter,													//Intersection position of the circle - input
	CSD1130::Vec2 &ptEnd,															//Final position of the circle after reflection - output
	CSD1130::Vec2 &reflectedVectorNormalized);										//Normalized reflection vector - output

// Extra credits
void CollisionResponse_CircleCircle(CSD1130::Vec2 &normal,							//Normal vector of reflection on collision time - input
	const float interTime,													//Intersection time - input
	CSD1130::Vec2 &velA,															//Velocity of CircleA - input
	const float &massA,														//Mass of CircleA - input
	CSD1130::Vec2 &interPtA,														//Intersection position of circle A at collision time - input
	CSD1130::Vec2 &velB,															//Velocity of CircleB - input
	const float &massB,														//Mass of CircleB - input
	CSD1130::Vec2 &interPtB,														//Intersection position of circle B at collision time - input
	CSD1130::Vec2 &reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
	CSD1130::Vec2 &ptEndA,															//Final position of the circle A after reflection - output
	CSD1130::Vec2 &reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
	CSD1130::Vec2 &ptEndB);														//Final position of the circle B after reflection - output



#endif // CSD1130_COLLISION_H_