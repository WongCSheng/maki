/*!
@file		glapp.cpp
@co-author	louishetong.wang@digipen.edu 
@co-author	thea@digipen.edu
@date		29/05/2022

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../Graphics/glhelper.h"
#include "../Game Object/GameObject.h"
#include "../Engine/Mesh/model.h"
#include "../Engine/Camera/Camera2D.h"
#include "../include/fonts.h"
#include "../Engine/Components/Physics/Physics.h"
#define M_PI									3.14159265358979323846  /* pi */
#include "../Engine/Texture/texture.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Game Object/Player.h"

/*                                                   objects with file scope
----------------------------------------------------------------------------- */

//define vps
std::vector<GLApp::GLViewport> GLApp::vps;
GLint polyMode = GL_FILL;
GLboolean f = GL_FALSE;
// create default engine as source of randomness
std::random_device rd;
std::default_random_engine dre(rd()* GL_TIME_ELAPSED);
GLint box_counter = 0;
GLint mystery_counter = 0;
std::map<std::string, GLSLShader>		GLApp::shdrpgms;
//Object temp;
GLSLShader shdr_pgm;

/*  _________________________________________________________________________ */
/*! init
@param none
@return none

Initialize color, viewports, VAO and create shader program
*/
void GLApp::init() {

	// clear colorbuffer with RGBA value in glClearColor
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// use entire window as viewport
	GLint w{ GLHelper::width }, h{ GLHelper::height };

	glViewport(0, 0, w, h);

	GLApp::vps.push_back({ 0, 0, 0, 0 });
	GLViewport{ vps[0].x, vps[0].y, vps[0].width, vps[0].height };
	// parse scene file $(SolutionDir)scenes/sushimi.scn
	// and store repo of models of type GLModel in container Model::models,
	// store shader programs of type GLSLShader in container GLApp::shdrpgms,
	// and store repo of objects of type GLObject in container Object::objects
	//sceneInitializer("../scenes/graphics_scene.txt");


	// Initialize camera here
	//Camera2D::camera2d.init(GLHelper::ptr_window, &Object::objects.at("Camera"));

	// uncomment these for errors
	//GLApp::insert_shdrpgm("Font", "../shaders/Font.vert", "../shaders/Font.frag");
	//Font::init();
	
	Shaders = make_unique<ShaderLibrary>();
	player = new Player();
}


/*  _________________________________________________________________________ */
/*! insert_shdrpgm
@param none
@return none

insert shader program into container GLApp::shdrpgms
*/
void GLApp::insert_shdrpgm(std::string shdr_pgm_name, std::string vtx_shdr, std::string frg_shdr)
{
	std::vector<std::pair<GLenum, std::string>> shdr_files
	{
		std::make_pair(GL_VERTEX_SHADER, vtx_shdr),
		std::make_pair(GL_FRAGMENT_SHADER, frg_shdr)
	};
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked())
	{
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	// add compiled, linked and validated shader program to
	// std::map container GLApp::shdrpgms
	GLApp::shdrpgms[shdr_pgm_name] = shdr_pgm;
}


/*  _________________________________________________________________________ */
/*! GLApp::update()
@param
@return none

Update the camera, then loop through objects and update all objects EXCEPT the camera
*/
void GLApp::update()
{
	// first, update camera
	//Camera2D::camera2d.update(GLHelper::ptr_window);
	//
	//// next, iterate thru each element in container object
	//// for each object of type Object, call update function
	//// except for camera
	//for (auto& x : Object::objects)
	//{
	//	if (x.first != "Camera")
	//	{
	//		x.second.update(GLHelper::delta_time);
	//	}
	//}
	//

}

/*  _________________________________________________________________________ */
/*! GLApp::draw()
@param
@return none

Write information onto window title, clear colour buffer, draw everything before rendering camera
*/
void GLApp::draw()
{
	// write title stuffs similar to sample ...
	std::stringstream ss;
	ss << "SushiMi Engine | ";
	//ss << std::fixed << std::setprecision(2) << " Camera Position: (" << Camera2D::camera2d.pgo->position.x << ", ";
	//ss << Camera2D::camera2d.pgo->position.y << ") | ";
	//ss << std::fixed << std::setprecision(0) << " Orientation: " << Camera2D::camera2d.pgo->orientation.x << " | ";
	//ss << " Window height: " << Camera2D::camera2d.height << " | ";
	ss << std::fixed << std::setprecision(2) << "FPS: " << GLHelper::fps;
	glfwSetWindowTitle(GLHelper::ptr_window, ss.str().c_str());

	// clear back buffer as before ...
	glClear(GL_COLOR_BUFFER_BIT);

	// draw everything before rendering camera
	//for (auto const& x : Object::objects)
	//{
	//	if (x.first != "Camera")
	//	{
	//		x.second.draw();
	//	}
	//}
	//Object::objects["Camera"].draw();




	//Font::RenderText(GLApp::shdrpgms["font"], "This is sample text", 25.0f, 25.0f, 9.0f, glm::vec3(0.5, 0.8f, 0.2f));

	Shaders->Textured_Shader()->use();
	GLApp::starttime = glfwGetTime();
	Shaders->Textured_Shader()->Send_Mat4("model_matrx", *player->Transformation());
	player->draw(delta);
	GLApp::endtime = glfwGetTime();
	GLApp::delta = GLApp::endtime - GLApp::starttime;

}


/*  _________________________________________________________________________ */
/*! cleanup
@param none
@return none

empty for now
*/
void GLApp::cleanup() 
{

}
