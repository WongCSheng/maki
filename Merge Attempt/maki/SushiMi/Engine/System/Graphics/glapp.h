/*!
@file		glapp.h
@author		pghali@digipen.edu
@co-author  louishetong.wang@digipen.edu
@date		29/05/2022

This file contains the declaration of namespace GLApp that encapsulates the
functionality required to implement an OpenGL application including
compiling, linking, and validating shader programs
setting up geometry and index buffers,
configuring VAO to present the buffered geometry and index data to
vertex shaders,
configuring textures (in later labs),
configuring cameras (in later labs),
and transformations (in later labs).
*//*__________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#ifndef GLAPP_H
#define GLAPP_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Headers/STL_Header.h"
#include "../Engine/System/Graphics/glslshader.h"
#include "../Engine/System/Graphics/glhelper.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../Engine/Camera/Camera2D.h"
#include "../Engine/Mesh/model.h"

struct GLApp {
	/*  _________________________________________________________________________ */
	/*! init
	@param none
	@return none

	Initialize color, viewports, VAO and create shader program
	*/
	static void init();
	/*  _________________________________________________________________________ */
	/*! update
	@param none
	@return none

	calculate frame rate, swap buffer and linear interpolate over a certain amount of time for smooth transition
	*/
	static void update();
	/*  _________________________________________________________________________ */
	/*! draw
	@param none
	@return none

	draws the color buffer, the rectangular model from NDC coordinates to viewport, the title bar
	*/
	static void draw();
	/*  _________________________________________________________________________ */
	/*! cleanup
	@param none
	@return none

	empty for now
	*/
	static void cleanup();

	/*  _________________________________________________________________________ */
	/*! init_scene
	@param none
	@return none

	function to parse scene file
	*/
	static void init_scene(std::string);
	struct GLViewport
	{
		GLint x, y;
		GLsizei width, height;
	};
	using VPSS = std::vector<std::pair<std::string, std::string>>;
	static std::map<std::string, GLSLShader> shdrpgms; // singleton
	static std::vector<GLViewport> vps; // container for viewports


};

#endif /* GLAPP_H */
