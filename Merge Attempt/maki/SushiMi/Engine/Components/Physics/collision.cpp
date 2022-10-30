//******************************************************************************/
/*!
\file		Collision.cpp
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\date   	2/8/2022
\brief		This source file contains the function definitions for
			building line segment, checking for collision between line segment
			and circles, and the response when collision occurs.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "collision.h"


double g_dt = GLHelper::delta_time;

/**************************************************************************/
/*!
* \brief		structure for the axis bound binding box
* \param		aabb1 - the first rectangle to checked for collision with the second rectangle
* \param		aabb2 - the second rectangle to checked for collision with the first rectangle
* \param		vel1, the velocity that is set to 0 (vel1-vel1 = 0)
* \param		vel2, the velocity that is set to the resultant velocity (vel2-vel1 = vRel)
* \return		bool, 0 if no collision/intersection and 1 if there is collision/intersection

*/
/**************************************************************************/
namespace Core
{
	bool Collision::CollisionIntersection_RectRect(const AABB& aabb1, const gfxVector2& vel1,
		const AABB& aabb2, const gfxVector2& vel2)
	{

		/*
		Implement the collision intersection over here.

		The steps are:
		Step 1: Check for static collision detection between rectangles (before moving).
					If the check returns no overlap you continue with the following next steps (dynamics).
					Otherwise you return collision true

		Step 2: Initialize and calculate the new velocity of Vb
				tFirst = 0
				tLast = dt

		Step 3: Working with one dimension (x-axis).
				if(Vb < 0)
					case 1
					case 4
				if(Vb > 0)
					case 2
					case 3

				case 5

		Step 4: Repeat step 3 on the y-axis

		Step 5: Otherwise the rectangles intersect

		*/
		double tFirst = 0.f;
		double tLast = g_dt;
		double dFirst = 0.f, dLast = 0.f;
		if (aabb1.max.y < aabb2.min.y || aabb1.max.x < aabb2.min.x || aabb1.min.y > aabb2.max.y || aabb1.min.x > aabb2.max.x) //if no overlap, continue
		{
			return 0;
		}

		/***************************************/
		// working with x-axis
		/***************************************/
		if ((vel2.x - vel1.x) < 0.f) //case 1 & 4
		{
			if (aabb1.min.x > aabb2.max.x) //case 1
			{
				return 0;
			}
			if (aabb1.max.x < aabb2.min.x) //case 4  (1/2)
			{
				dFirst = aabb1.max.x - aabb2.min.x;
				tFirst = dFirst / (vel2.x - vel1.x);

			}
			if (aabb1.min.x < aabb2.max.x) //case 4  (2/2)
			{

				dLast = aabb1.min.x - aabb2.max.x;
				tLast = dLast / (vel2.x - vel1.x);
			}
		}
		if ((vel2.x - vel1.x) > 0.f) //case 2 & case 3
		{
			if (aabb1.min.x > aabb2.max.x) //case 2 (1/2)
			{
				dFirst = aabb1.min.x - aabb2.max.x;
				tFirst = dFirst / (vel2.x - vel1.x);



			}
			if (aabb1.max.x < aabb2.min.x) //case 2 (2/2)
			{

				dLast = aabb1.max.x - aabb2.min.x;
				tLast = dLast / (vel2.x - vel1.x);

			}
			if (aabb1.max.x < aabb2.min.x) //case 3
			{
				return 0;
			}
			if (tFirst > g_dt)
			{
				return 0;
			}
		}
		//case 5:
		if (tFirst > tLast) { return 0; } //no collision


		/***************************************/
		// working with y-axis
		/***************************************/
		if ((vel2.y - vel1.y) < 0.f) //case 1 & 4
		{
			if (aabb1.min.y > aabb2.max.y) //case 1
			{
				return 0;
			}
			if (aabb1.max.y < aabb2.min.y) //case 4 revisited (1/2)
			{
				dFirst = aabb1.max.y - aabb2.min.y;
				tFirst = max((dFirst) / (vel2.y - vel1.y), tFirst);

			}
			if (aabb1.min.y < aabb2.max.y) //case 4 revisited (2/2)
			{

				dLast = aabb1.min.y - aabb2.max.y;
				tLast = min((dLast) / (vel2.y - vel1.y), tLast);
			}
		}
		if ((vel2.y - vel1.y) > 0.f) //case 2 & case 3
		{
			if (aabb1.min.y > aabb2.max.y) //case 2 (1/2)
			{
				dFirst = aabb1.min.y - aabb2.max.y;
				tFirst = max((dFirst) / (vel2.y - vel1.y), tFirst);



			}
			if (aabb1.max.y < aabb2.min.y) //case 2 (2/2)
			{

				dLast = aabb1.max.y - aabb2.min.y;
				tLast = min((dLast) / (vel2.y - vel1.y), tLast);

			}
			if (aabb1.max.y < aabb2.min.y) //case 3
			{
				return 0; //no intersection
			}
		}
		//case 5:
		if (tFirst > tLast) { return 0; } //no collision
		//std::cout << "Collision Detected!" << std::endl;
		return 1; //collision
	}

	/******************************************************************************/
	/*!
	* * This function builds a line segment where it's position for p0 and p1 is
		calculated using the parameters pos, scale and dir.
		*/
		/******************************************************************************/
	void Collision::BuildLineSegment(LineSegment& lineSegment,
		const gfxVector2& pos,
		float scale,
		float dir)
	{
		gfxVector2 temp(scale, 0);

		temp = { temp.x * cos(dir) - sin(dir) * temp.y, temp.x * sin(dir) + cos(dir) * temp.y };

		lineSegment.m_pt0 = pos - temp * 0.5;
		lineSegment.m_pt1 = pos + temp * 0.5;

		gfxVector2 NormalVec;

		NormalVec.Normalize(NormalVec, temp);

		lineSegment.m_normal = { NormalVec.y, -NormalVec.x };
	}

	/******************************************************************************/
	/*!
	* * This function checks for collision between a circle and line segment
		*/
		/******************************************************************************/
		//int CollisionIntersection_CircleLineSegment(const Circle &circle,
		//	const gfxVector2&ptEnd,
		//	const LineSegment &lineSeg,
		//	gfxVector2&interPt,
		//	gfxVector2&normalAtCollision,
		//	float &interTime,
		//	bool & checkLineEdges)
		//{
		//	
		//	UNREFERENCED_PARAMETER(checkLineEdges);
		//
		//	gfxVector2 normal, m, vel, p0prime, p1prime;
		//	vel = ptEnd - circle.m_center;
		//	m.m[0] = m.x = vel.y;
		//	m.m[1] = m.y = -vel.x;
		//	CSD1130::Vector2DNormalize(normal, lineSeg.m_normal); 
		//	normalAtCollision = normal;
		//	if ((CSD1130::Vector2DDotProduct(circle.m_center, normal) - (CSD1130::Vector2DDotProduct(lineSeg.m_pt0, normal))) <= -circle.m_radius)
		//	{
		//		p0prime = lineSeg.m_pt0 - circle.m_radius * normal;
		//		p1prime = lineSeg.m_pt1 - circle.m_radius * normal;
		//
		//
		//		if (CSD1130::Vector2DDotProduct(m, (p0prime - circle.m_center)) * CSD1130::Vector2DDotProduct(m, (p1prime - circle.m_center)) < 0)
		//		{
		//
		//			
		//			interTime = (CSD1130::Vector2DDotProduct(normal, lineSeg.m_pt0) - CSD1130::Vector2DDotProduct(normal, circle.m_center) - circle.m_radius)
		//				/ (CSD1130::Vector2DDotProduct(normal, vel));
		//
		//			if (interTime >= 0 && interTime <= 1)
		//			{
		//				interPt = circle.m_center + vel * interTime;
		//
		//				return 1;
		//
		//			}
		//			else
		//			{
		//				return 0;
		//			}
		//		}
		//
		//	}
		//	else if ((CSD1130::Vector2DDotProduct(circle.m_center, normal) - (CSD1130::Vector2DDotProduct(lineSeg.m_pt0, normal))) >= circle.m_radius)
		//	{
		//		p0prime = lineSeg.m_pt0 + circle.m_radius * normal;
		//		p1prime = lineSeg.m_pt1 + circle.m_radius * normal;
		//
		//
		//		if (CSD1130::Vector2DDotProduct(m, (p0prime - circle.m_center)) * CSD1130::Vector2DDotProduct(m, (p1prime - circle.m_center)) < 0)
		//		{
		//
		//			interTime = (CSD1130::Vector2DDotProduct(normal, lineSeg.m_pt0) - CSD1130::Vector2DDotProduct(normal, circle.m_center) + circle.m_radius)
		//				/ (CSD1130::Vector2DDotProduct(normal, vel));
		//
		//			if (interTime >= 0 && interTime <= 1)
		//			{
		//				interPt = circle.m_center + vel * interTime;
		//
		//				return 1;
		//
		//			}
		//			else
		//			{
		//				return 0;
		//			}
		//		}
		//	}
		//	else
		//	{
		//		return 0;
		//	}
		//	return 0; 
		//}

		/******************************************************************************/
		/*!
		** Function to check if circle is moving to the edge of the line
		*/
		/******************************************************************************/
		//int CheckMovingCircleToLineEdge(bool withinBothLines,
		//	const Circle &circle,
		//	const CSD1130::Vec2 &ptEnd,
		//	const LineSegment &lineSeg,
		//	CSD1130::Vec2 &interPt,
		//	CSD1130::Vec2 &normalAtCollision,
		//	float &interTime)		
		//{
		//	UNREFERENCED_PARAMETER(withinBothLines);
		//	UNREFERENCED_PARAMETER(circle);
		//	UNREFERENCED_PARAMETER(ptEnd);
		//	UNREFERENCED_PARAMETER(lineSeg);
		//	UNREFERENCED_PARAMETER(interPt);
		//	UNREFERENCED_PARAMETER(normalAtCollision);
		//	UNREFERENCED_PARAMETER(interTime);
		//	return 0;
		//}

		/******************************************************************************/
		/*!
		** This functioon checks for circle circle collision
		*/
		/******************************************************************************/
		//int CollisionIntersection_CircleCircle(const Circle &circleA,
		//	const gfxVector2&velA,
		//	const Circle &circleB,
		//	const gfxVector2&velB,
		//	gfxVector2&interPtA,
		//	gfxVector2&interPtB,
		//	float &interTime)
		//{
		//	gfxVector2 v_rel_A;
		//	v_rel_A = velA - velB; 
		//
		//	Ray temp_ray;
		//	Circle temp_circle;
		//	temp_ray.m_dir = v_rel_A;
		//	temp_ray.m_pt0 = circleA.m_center;
		//	temp_circle.m_center = circleB.m_center;
		//	temp_circle.m_radius = circleA.m_radius + circleB.m_radius;
		//	if (CollisionIntersection_RayCircle(temp_ray, temp_circle, interTime))
		//	{
		//		interPtA = circleA.m_center + velA * interTime;
		//		interPtB = circleB.m_center + interTime * velB; //cB is just 0
		//		return 1;
		//	}
		//
		//	return 0;
		//
		//	
		//}

		/******************************************************************************/
		/*!
		** This function checks for collision of ray with circle
		*/
		/******************************************************************************/
		//int CollisionIntersection_RayCircle(const Ray &ray,
		//	const Circle &circle,
		//	float &interTime)
		//{
		//	
		//
		//	gfxVector2 temp;
		//	temp.Normalize(temp, ray.m_dir); //v
		//
		//	//float proj_dist_m = CSD1130::Vector2DDotProduct(circle.m_center - ray.m_pt0, temp);
		//	float dist_0_sq;
		//	float inter_0;
		//	float calculated_s;
		//
		//	//if (proj_dist_m < 0 && (CSD1130::Vector2DLength(circle.m_center - ray.m_pt0) > circle.m_radius)) //If 0 && outside circle m < B
		//	//{
		//	//	return 0; 
		//	//}
		//	//dist_0_sq = CSD1130::Vector2DSquareLength(circle.m_center - ray.m_pt0) - proj_dist_m * proj_dist_m; //dist0 ^2 = BsC^2 - m^2
		//	if (dist_0_sq > (circle.m_radius * circle.m_radius))
		//	{
		//		return 0; 
		//	}
		//
		//	calculated_s = sqrt((circle.m_radius * circle.m_radius) - dist_0_sq);
		//	//inter_0 = (proj_dist_m - calculated_s) / (CSD1130::Vector2DLength(ray.m_dir));
		//
		//
		//	if (inter_0 >= 0 && inter_0 <= 1)
		//	{
		//		interTime = inter_0;
		//		return 1;
		//	}
		//	
		//	return 0;
		//}


		/******************************************************************************/
		/*!
		** This function implements the response after a collision between circle and line segment
		*/
		/******************************************************************************/
		//void CollisionResponse_CircleLineSegment(const CSD1130::Vec2 &ptInter,
		//	const CSD1130::Vec2 &normal,
		//	CSD1130::Vec2 &ptEnd,
		//	CSD1130::Vec2 &reflected)
		//{
		//	CSD1130::Vec2 pen = ptEnd - ptInter;
		//	ptEnd = ptInter + pen - 2 * (CSD1130::Vector2DDotProduct(pen, normal) * normal);
		//	reflected = ptEnd - ptInter;
		//	CSD1130::Vector2DNormalize(reflected, reflected);
		//}

		/******************************************************************************/
		/*!
		** This function implements the response after a collision between circle and pillar
			*/
			/******************************************************************************/
			//void CollisionResponse_CirclePillar(const CSD1130::Vec2 &normal,
			//	const float &interTime,
			//	const CSD1130::Vec2 &ptStart,
			//	const CSD1130::Vec2 &ptInter,
			//	CSD1130::Vec2 &ptEnd,
			//	CSD1130::Vec2 &reflectedVectorNormalized)
			//{
			//	UNREFERENCED_PARAMETER(ptStart);
			//	UNREFERENCED_PARAMETER(interTime);
			//	CSD1130::Vec2 pen = ptEnd - ptInter;
			//	ptEnd = ptInter + pen - 2 * (CSD1130::Vector2DDotProduct(pen, normal) * normal);
			//	reflectedVectorNormalized = ptEnd - ptInter;
			//	CSD1130::Vector2DNormalize(reflectedVectorNormalized, reflectedVectorNormalized);
			//}

			/******************************************************************************/
			/*!
				Extra credits
			*/
			/******************************************************************************/

			//void CollisionResponse_CircleCircle(gfxVector2 &normal,
			//	const float interTime,
			//	gfxVector2&velA,
			//	const float &massA,
			//	gfxVector2&interPtA,
			//	gfxVector2&velB,
			//	const float &massB,
			//	gfxVector2&interPtB,
			//	gfxVector2&reflectedVectorA,
			//	gfxVector2&ptEndA,
			//	gfxVector2&reflectedVectorB,
			//	gfxVector2&ptEndB)
			//{
			//	UNREFERENCED_PARAMETER(normal);
			//	UNREFERENCED_PARAMETER(interTime);
			//	UNREFERENCED_PARAMETER(velA);
			//	UNREFERENCED_PARAMETER(massA);
			//	UNREFERENCED_PARAMETER(interPtA);
			//	UNREFERENCED_PARAMETER(velB);
			//	UNREFERENCED_PARAMETER(massB);
			//	UNREFERENCED_PARAMETER(interPtB);
			//	UNREFERENCED_PARAMETER(reflectedVectorA);
			//	UNREFERENCED_PARAMETER(ptEndA);
			//	UNREFERENCED_PARAMETER(reflectedVectorB);
			//	UNREFERENCED_PARAMETER(ptEndB);
			//}
}