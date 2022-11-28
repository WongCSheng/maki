/*!
@file    SushiMi.vert
@author  louishetong.wang@digipen.edu
@date    19/09/2022

This file implements per-vertex operations to set up the
vertex shader to read per-vertex data into vertex attributes defined in the vertex shader from
these vertex attribute indices. 
Added uniform matrix for tut3

*//*__________________________________________________________________________*/

#version 450 core

layout (location=0) in vec2 aVertexPosition;

//layout (location=1) in vec3 aVertexColor;

//layout (location=0) out vec3 vColor;

uniform mat3 uModel_to_NDC;
/*  _________________________________________________________________________ */
/*! main

@param none

@return none

convert x,y values into 4 components(x,y,0.0,1.0) using vec4 constructor.
Then, assign unchanged copy of per-vertex colour from in variable to out variable
*/
void main()
{
	gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)),
					0.0, 1.0);

	//vColor = aVertexColor;
}