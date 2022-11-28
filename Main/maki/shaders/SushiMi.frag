/*!
@file    SushiMi.frag
@author  louishetong.wang@digipen.edu
@date    18/09/2022

This file takes in the interpolated colour and determine the corresponding fragment colour.
The vertex shaders' outputs must correspond to the fragment shaders' inputs: inputs and outputs
must match by name, type, and qualifiers exactly.

*//*__________________________________________________________________________*/

#version 450 core
/*
A per-fragment color attribute is no longer received from rasterizer.
Instead per-fragment color attribute is supplied by the application to
a uniform variable:
uniform vec3 uColor;
The uniform variable will retain the value for every invocation of the
fragment shader. That is why every fragment of the triangle primitive
rendered by an object has the same color
*/

//layout(location=0) in vec3 vColor;
uniform vec3 uColor;
layout (location=0) out vec4 fFragColor;

void main() {
//fFragColor = vec4(vColor, 1.0);
fFragColor = vec4(uColor, 1.0);
}
