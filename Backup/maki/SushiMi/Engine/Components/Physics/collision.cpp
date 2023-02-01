//******************************************************************************/
/*!
\file		Collision.cpp
\author 	Thea Sea
\par    	email: thea.sea@digipen.edu
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
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
	void Collision::Init()
	{
	}

	void Collision::Serialise(const std::string name)
	{

	}

	void Collision::Deserialise(const std::string name)
	{

	}

	void Remove()
	{

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
	\brief		This function takes in a circle and a rectangle and calculates the distance
				between the two parameters
	\param		 c    (circle)
	\param		 rect (rectangle)
	/******************************************************************************/
	float getDistance(gfxVector2 c, gfxVector2 rect)
	{
		//distance from bottom left of rect to center of circle
		float distanceX = std::pow((rect.x - c.x), 2);  //(x2-x1)^2
		float distanceY = std::pow((rect.y - c.y), 2);  //(y2-y1)^2
		float distance = std::sqrt(distanceX + distanceY);
		return distance;
	}

	/**************************************************************************/
	/*!
	* \brief		collision detection for Circle&Rectangle collisions
	* \param		OBB & circle - the circle object to check for collision (against the rectangle)
	* \param		AABB & aabb- the rectangle to checked for collision with the circle
	* \return		bool(result), 0 if no collision/intersection and 1 if there is collision/intersection

	*/
	/**************************************************************************/
	bool CollisionIntersection_CircleRect(OBB& circle, AABB& aabb)
	{
		//left edge
		float recMin_x = aabb.min.x;
		float recMin_y = aabb.min.y;
		//right edge
		float recMax_x = aabb.max.x;
		float recMax_y = aabb.max.y;

		float result = false;
		//gfxVector2 center = circle.center; //for nicer code , later clean up
		float center_x = circle.center.x;
		float center_y = circle.center.y;
		float radius = circle.radius;

		if ((center_x >= recMin_x - radius) && (center_x <= recMax_x + radius) && (center_y >= recMin_y) && (center_y <= recMax_y))
		{
			result = true;
		}
		else if ((center_x >= recMin_x) && (center_x <= recMax_x) && (center_y >= recMin_y - radius) && (center_y <= recMax_y + radius))
		{
			result = true;
		}
		else
		{
			//calculate  bottom
			float bottom_left__to_center = getDistance({ center_x, center_y }, { recMin_x, recMin_y });
			float bottom_right__to_center = getDistance({ center_x, center_y }, { recMax_x, recMin_y });

			//calculate top 
			float top_left__to_center = getDistance({ center_x, center_y }, { recMin_x, recMax_y });
			float top_right__to_center = getDistance({ center_x, center_y }, { recMax_x, recMax_y });

			//check for colliding, ( if distance < circle.radius, they're colliding )
			if ((bottom_left__to_center <= circle.radius) || (top_left__to_center <= circle.radius)
				|| (bottom_right__to_center <= circle.radius) || (top_right__to_center <= circle.radius))
			{
				result = true;
			}
		}
		return result;

	}

	bool staticPointRect(gfxVector2 const& point, AABB const& rect)
	{
		if (point.x > rect.min.x && point.x < rect.max.x)
		{
			if (point.y > rect.min.y && point.y < rect.max.y)
			{
				return true;
			}
			return false;
		}
		else
			return false;

	}

	AABB& Collision::GetAABB()
	{
		return boundingBox;
	}

	gfxVector2& Collision::GetvelCurr()
	{
		return velCurr;
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