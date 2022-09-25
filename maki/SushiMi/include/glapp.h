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
#include "../include/glslshader.h"
#include "../include/glhelper.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <array>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>
#include <random>
#ifndef GLAPP_H
#define GLAPP_H

/*                                                                   includes
----------------------------------------------------------------------------- */

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
	// encapsulates geometry - we call this abstraction a model
	struct GLModel {
		GLenum primitive_type{}; // which OpenGL primitive to be rendered?
		//GLSLShader shdr_pgm; // no longer required in tut 3
		GLuint vaoid{}; // handle to VAO
		GLuint draw_cnt{}; // count of vertices for certain type of primitives and a count of indices for other types
		//Gluint idx_elem_cnt // removed for  tut 2
		GLuint primitive_cnt{}; // access the number of OGL pimitives contained in an instance of GLModel
								// primitive_type are to be rendered
		/*  _________________________________________________________________________ */
		/*! GLModel init(std::string)
		@param std::string
		@return GLModel result

		initialize the 3 different types of models by reading from the filepath and storing the data into a model.
		*/
		GLApp::GLModel init(std::string mesh_filepath); // read mesh data from file ...
	};


	// tutorial 3: encapsulates state required to update
	// and render an instance of a model
	struct GLObject
	{
		glm::vec2 orientation{}; // orientation.x is angle_disp and
							  // orientation.y is angle_speed both in degrees

		glm::vec2 scaling{}; // scaling parameters
		glm::vec2 position{}; // translation vector coordinates

		// compute object's model transform matrix using scaling,
		// rotation, and translation attributes ...
		// this must be computed by the cpu and not by the vertex shader (why?)
		glm::mat3 mdl_to_ndc_xform{};

		// which model is this object an instance of?
		// since models are contained in a vector, we keep track of the
		// specific model that was instanced by index into vector container
		std::map<std::string, GLApp::GLModel>::iterator mdl_ref{};

		// how to draw this instanced model?
		// since shader programs are contained in a vector, we keep track of
		// specific shader program using an index into vector container
		std::map<std::string, GLSLShader>::iterator shd_ref{};

		// added in tut 4
		glm::vec3 color{};
		glm::mat3 mdl_xform{}; // model transformation

		// member functions that must be defined in glapp.cpp

		/*  _________________________________________________________________________ */
		/*! GLObject::draw() const
		@param none
		@return none

		Install shader program using GLSLShader::Use();
		Bind object's VAO handle
		Copy object's NDC matrix to vertex shader
		Render using GLDrawElements
		Clean up by unbinding and deinstall shader program
		*/
		void draw() const;

		/*  _________________________________________________________________________ */
		/*! GLObject::update(GLDouble delta_time)
		@param GLDouble delta_time
		@return none

		all the matrix transformations are here
		scaling, rotation+transformation and window_ndc scaling
		*/
		void update(GLdouble delta_time);
	};
	struct Camera2D
	{
		GLObject* pgo{}; // pointer to game object that embeds camera
		glm::vec2 right{}, up{};

		// additional parameters
		GLint height{ 1000 };
		GLfloat ar{};
		glm::mat3 camwin_to_ndc_xform{}, world_to_ndc_xform{}, view_xform{};

		// window change parameters
		GLint min_height{ 500 }, max_height{ 2000 };
		// height is increasing if 1 and decreasing if -1
		GLint height_chg_dir{ 1 };
		// increments by which window height is changed per Z key press
		GLint height_chg_val{ 5 };

		// camera speed when button U is pressed
		GLfloat linear_speed{ 2.f };

		// Keyboard button press flags:
		GLboolean camtype_flag{ GL_FALSE }; // button V
		GLboolean zoom_flag{ GL_FALSE }; // button Z
		GLboolean left_turn_flag{ GL_FALSE }; // button H
		GLboolean right_turn_flag{ GL_FALSE }; // button K
		GLboolean move_flag{ GL_FALSE }; // button U

		/*  _________________________________________________________________________ */
		/*! GLApp::Camera2D::init(GLFWwindow* pWindow, GLApp::GLObject* ptr)
		@param GLFWwindow* pWindow, GLApp::GLObject* ptr
		@return none

		Assign pgo to camera and compute aspect ratio, initialize as free camera.
		*/
		void init(GLFWwindow*, GLObject* ptr);
		/*  _________________________________________________________________________ */
		/*! GLApp::Camera2D::update(GLFWwindow*)
		@param GLFWwindow*
		@return none

		Update camera's ratio, orientation, position, up and right vectors, zoom and transformation matrices
		*/
		void update(GLFWwindow*);
	};
	static Camera2D camera2d;
	static std::vector<GLViewport> vps; // container for viewports
	static std::map<std::string, GLSLShader> shdrpgms; // singleton
	static std::map<std::string, GLModel> models; // singleton
	static std::map<std::string, GLObject> objects; // singleton

};

#endif /* GLAPP_H */
