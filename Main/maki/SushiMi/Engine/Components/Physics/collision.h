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

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../Headers/STL_Header.h"
#include "../Headers/Math_Header.h"
#include "../Engine/System/Graphics/glhelper.h"
#include "../Component.h"

namespace Core
{
	/**************************************************************************/
	/*!
	* \brief		structure for the axis bound binding box
	* \param		none, not a function
	* \return		none, not a function
	*/
	/**************************************************************************/
	struct AABB
	{
		//AEVec2	c; // center
		//float  r[2]; // holds half width and half height

		gfxVector2	min;
		gfxVector2	max;
	};
	/**************************************************************************/
	/*!
	* \brief		structure for the axis bound binding box (circle_rec)
	* \param		none, not a function
	* \return		none, not a function
	*/
	/**************************************************************************/
	struct OBB
	{
		gfxVector2 center; //center of circle
		float radius;		//circle radius
	};

	bool CollisionIntersection_CircleRect(OBB& circle, AABB& aabb);
	bool staticPointRect(gfxVector2 const& point, AABB const& rect);


	/******************************************************************************/
		/*!
			Struct for line segment
		 */
		 /******************************************************************************/
	struct LineSegment
	{
		gfxVector2	m_pt0;
		gfxVector2	m_pt1;
		gfxVector2	m_normal;
	};

	struct VertexList
	{
		int mpVtxBuffer;
		int	vtxNum;
	};

	typedef struct Mtx33 //Why not use gfxMatrix3??
	{
		float	m[3][3];
	}Mtx33;

	class Collision : public Component 
	{

	public:

		double g_dt = GLHelper::delta_time;

		Collision() {}
		~Collision() {}

		void Init();
		void Serialise(const std::string name);


		void BuildLineSegment(LineSegment& lineSegment,								//Line segment reference - input
			const gfxVector2& pos,									//position - input
			float scale,											//scale - input
			float dir);											//direction - input

		AABB& GetAABB();
		gfxVector2& GetvelCurr();

	private:

		unsigned long type{ 0 };		// object type
		VertexList* pMesh{ 0 };		// This will hold the triangles which will form the shape of the object

		unsigned long		flag{ 0 };		// bit flag or-ed together
		float				scale{ 0 };		// scaling value of the object instance
		gfxVector2			posCurr{ 0,0 };	// object current position
		gfxVector2			velCurr{ 0,0 };	// object current velocity
		float				dirCurr{ 0 };	// object current direction
		AABB				boundingBox{ {0,0},{0,0} };// object bouding box that encapsulates the object
		Mtx33				transform{ 0 };	// object transformation matrix: Each frame, 


		/******************************************************************************/
		/*!
		 */
		 /******************************************************************************/
		 //struct Circle
		 //{
		 //	CSD1130::Vec2  m_center;
		 //	float	m_radius;
		 //
		 //	// Extra credits
		 //	float   m_mass{ 1.0f };
		 //};
		 //
		 //struct Ray
		 //{
		 //	CSD1130::Vec2	m_pt0;
		 //	CSD1130::Vec2	m_dir;
		 //};
		 //
		 //
		 //// INTERSECTION FUNCTIONS
		 //int CollisionIntersection_CircleLineSegment(const Circle &circle,			//Circle data - input
		 //	const CSD1130::Vec2 &ptEnd,													//End circle position - input
		 //	const LineSegment &lineSeg,												//Line segment - input
		 //	CSD1130::Vec2 &interPt,														//Intersection point - output
		 //	CSD1130::Vec2 &normalAtCollision,												//Normal vector at collision time - output
		 //	float &interTime,														//Intersection time ti - output
		 //	bool & checkLineEdges);													//The last parameter is new - for Extra Credits: true = check collision with line segment edges
		 //
		 //// Extra credits
		 //int CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
		 //	const Circle &circle,													//Circle data - input
		 //	const CSD1130::Vec2 &ptEnd,													//End circle position - input
		 //	const LineSegment &lineSeg,												//Line segment - input
		 //	CSD1130::Vec2 &interPt,														//Intersection point - output
		 //	CSD1130::Vec2 &normalAtCollision,												//Normal vector at collision time - output
		 //	float &interTime);														//Intersection time ti - output
		 //
		 //
		 //// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
		 //// In the case of "dynamic circle vs static pillar", velB will be 0.0f
		 //int CollisionIntersection_CircleCircle(const Circle &circleA,				//CircleA data - input
		 //	const CSD1130::Vec2 &velA,														//CircleA velocity - input
		 //	const Circle &circleB,													//CircleB data - input
		 //	const CSD1130::Vec2 &velB,														//CircleA velocity - input
		 //	CSD1130::Vec2 &interPtA,														//Intersection point of CircleA at collision time - output
		 //	CSD1130::Vec2 &interPtB,														//Intersection point of CircleB at collision time - output
		 //	float &interTime);														//intersection time - output
		 //
		 //// circle-circle - same usage for: dynamic circle vs static pillar, and dynamic circle vs dynamic circle
		 //// this is a helper function to be used inside "CollisionIntersection_CircleCircle" function
		 //// it is checking collision a moving dot vs a static circle
		 //int CollisionIntersection_RayCircle(const Ray &ray,							//A ray containing the data of the moving dot - input
		 //	const Circle &circle,													//Static circle data - input
		 //	float &interTime);														//Intersection time - output
		 //
		 //
		 //
		 //
		 //
		 //
		 //// RESPONSE FUNCTIONS
		 //void CollisionResponse_CircleLineSegment(const CSD1130::Vec2 &ptInter,				//Intersection position of the circle - input
		 //	const CSD1130::Vec2 &normal,													//Normal vector of reflection on collision time - input
		 //	CSD1130::Vec2 &ptEnd,															//Final position of the circle after reflection - output
		 //	CSD1130::Vec2 &reflected);														//Normalized reflection vector direction - output
		 //
		 //void CollisionResponse_CirclePillar(const CSD1130::Vec2 &normal,					//Normal vector of reflection on collision time - input
		 //	const float &interTime,													//Intersection time - input
		 //	const CSD1130::Vec2 &ptStart,													//Starting position of the circle - input
		 //	const CSD1130::Vec2 &ptInter,													//Intersection position of the circle - input
		 //	CSD1130::Vec2 &ptEnd,															//Final position of the circle after reflection - output
		 //	CSD1130::Vec2 &reflectedVectorNormalized);										//Normalized reflection vector - output
		 //
		 //// Extra credits
		 //void CollisionResponse_CircleCircle(CSD1130::Vec2 &normal,							//Normal vector of reflection on collision time - input
		 //	const float interTime,													//Intersection time - input
		 //	CSD1130::Vec2 &velA,															//Velocity of CircleA - input
		 //	const float &massA,														//Mass of CircleA - input
		 //	CSD1130::Vec2 &interPtA,														//Intersection position of circle A at collision time - input
		 //	CSD1130::Vec2 &velB,															//Velocity of CircleB - input
		 //	const float &massB,														//Mass of CircleB - input
		 //	CSD1130::Vec2 &interPtB,														//Intersection position of circle B at collision time - input
		 //	CSD1130::Vec2 &reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
		 //	CSD1130::Vec2 &ptEndA,															//Final position of the circle A after reflection - output
		 //	CSD1130::Vec2 &reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
		 //	CSD1130::Vec2 &ptEndB);														//Final position of the circle B after reflection - output

	};
}

#endif // CSD1130_COLLISION_H_