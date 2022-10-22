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
#include <../include/glapp.h>
#include <../include/glhelper.h>
#include <../object.h>
#include <../model.h>
#include <../Camera2D.h>
#include <../fonts.h>
#include <../Physics.h>
#define M_PI									3.14159265358979323846  /* pi */


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
Object temp;
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
	GLApp::init_scene("../scenes/SushiMiscene.scn");


	// Initialize camera here
	Camera2D::camera2d.init(GLHelper::ptr_window, &Object::objects.at("Camera"));
	

	// font testing

}


/*  _________________________________________________________________________ */
/*! insert_shdrpgm
@param none
@return none

insert shader program into container GLApp::shdrpgms
*/
void insert_shdrpgm(std::string shdr_pgm_name, std::string vtx_shdr, std::string frg_shdr)
{
	std::vector<std::pair<GLenum, std::string>> shdr_files
	{
		std::make_pair(GL_VERTEX_SHADER, vtx_shdr),
		std::make_pair(GL_FRAGMENT_SHADER, frg_shdr)
	};
	GLSLShader shdr_pgm;
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
/*! init_scene
@param none
@return none

function to parse scene file
*/
void GLApp::init_scene(std::string scene_filename)
{
	std::ifstream ifs{ scene_filename, std::ios::in };
	if (!ifs)
	{
		std::cout << "ERROR: Unable to open scene file: " << scene_filename << std::endl;
		exit(EXIT_FAILURE);
	}
	ifs.seekg(0, std::ios::beg);

	std::string line;
	getline(ifs, line); // first line is count of objects in scene
	std::istringstream line_sstm{ line };
	int obj_cnt;
	line_sstm >> obj_cnt; // read count of objs in scene
	while (obj_cnt--) // read each object's param
	{
		std::string mesh_path;
		Object currObj;
		getline(ifs, line); // 1st parameter: model's name
		std::istringstream line_modelname{ line };
		std::string model_name;
		line_modelname >> model_name;

		//find model with the same name
		std::map<std::string, Model>::iterator mdl_iterator;
		mdl_iterator = Model::models.find(model_name);
		 
		bool hasMass = false;

		if (mdl_iterator == Model::models.end())
		{
			Model curr_mdl;
			if (model_name == "circle")
			{
				mesh_path = "../mesh/circle.msh";
				curr_mdl.primitive_type = GL_TRIANGLE_FAN;
				currObj.mass = 10.0f;
				//hasMass = true;
				//currObj.status = true; //alive

			}
			else if (model_name == "square")
			{
				mesh_path = "../mesh/square.msh";
				curr_mdl.primitive_type = GL_TRIANGLES;
			}
			else if (model_name == "triangle")
			{
				mesh_path = "../mesh/triangle.msh";
				curr_mdl.primitive_type = GL_TRIANGLES;
			}
			else if (model_name == "linebox")
			{
				mesh_path = "../mesh/linebox.msh";
				curr_mdl.primitive_type = GL_LINE;
			}
			curr_mdl = curr_mdl.init(mesh_path);
			Model::models.insert(std::pair<std::string, Model>(model_name, curr_mdl));
			mdl_iterator = Model::models.find(model_name);
		}
		getline(ifs, line); // 2nd parameter: name of game object
		std::istringstream line_objname{ line };
		std::string object_name;
		line_objname >> object_name;
		getline(ifs, line); // 3rd parameter: names of shader program, vertex and fragment shaders for rendering model square
		std::istringstream line_shdrname{ line };
		std::string shdr_name, shdr_vert, shdr_frag;
		line_shdrname >> shdr_name >> shdr_vert >> shdr_frag;
		std::map<std::string, GLSLShader>::iterator shdr_iterator;
		shdr_iterator = shdrpgms.find(shdr_name);
		if (shdr_iterator == GLApp::shdrpgms.end())
		{
			insert_shdrpgm(shdr_name, shdr_vert, shdr_frag);
			shdr_iterator = shdrpgms.find(shdr_name);
		}
		getline(ifs, line); // 4th parameter: rgb colours used for painting object
		std::istringstream line_rgb{ line };
		GLfloat red, green, blue;
		line_rgb >> red >> green >> blue;

		currObj.color = { red, green, blue };

		getline(ifs, line); // 5th parameter: Scaling factors of object along horizontal and vertices axes, respectively.
		std::istringstream line_scale{ line };
		GLfloat scale_x, scale_y;
		line_scale >> scale_x >> scale_y;
		currObj.scaling = { scale_x, scale_y };

		getline(ifs, line); // 6th parameter: orientation factors of object: initial angular orientation
		std::istringstream line_orientation{ line };
		GLfloat orientation_x, orientation_y;
		line_orientation >> orientation_x >> orientation_y;
		currObj.orientation = { orientation_x, orientation_y };

		getline(ifs, line); // 7th factor: Obj's position in game world.
		std::istringstream line_pos{ line };
		GLfloat pos_x, pos_y;
		line_pos >> pos_x >> pos_y;
		currObj.position = { pos_x, pos_y };
		currObj.initialPos = { currObj.position };			//stores initial position for distance calculation

		//apply physics 
		if (hasMass == true)
		{
			getline(ifs, line);
			std::istringstream line_mass{ line }; //getting mass of obj
			float objMass;	//create mass inst
			line_mass >> objMass; // convert istream to float
			currObj.mass = objMass; //assign mass to currObj
			hasMass = false; // turn off
		 }
		/*
		if (currObj.status == true)
		{
			currObj.aabb.min.
		}
		*/
	
		currObj.mdl_ref = mdl_iterator;
		currObj.shd_ref = shdr_iterator;

		Object::objects.insert(std::pair<std::string, Object>(object_name, currObj));

	}

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
	Camera2D::camera2d.update(GLHelper::ptr_window);

	// next, iterate thru each element in container object
	// for each object of type Object, call update function
	// except for camera
	for (auto& x : Object::objects)
	{
		if (x.first != "Camera")
		{
			x.second.update(GLHelper::delta_time);
		}
	}
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
	ss << std::fixed << std::setprecision(2) << " Camera Position: (" << Camera2D::camera2d.pgo->position.x << ", ";
	ss << Camera2D::camera2d.pgo->position.y << ") | ";
	ss << std::fixed << std::setprecision(0) << " Orientation: " << Camera2D::camera2d.pgo->orientation.x << " | ";
	ss << " Window height: " << Camera2D::camera2d.height << " | ";
	ss << std::fixed << std::setprecision(2) << "FPS: " << GLHelper::fps;
	glfwSetWindowTitle(GLHelper::ptr_window, ss.str().c_str());

	// clear back buffer as before ...
	glClear(GL_COLOR_BUFFER_BIT);

	// draw everything before rendering camera
	for (auto const& x : Object::objects)
	{
		if (x.first != "Camera")
		{
			x.second.draw();
		}
	}
	Object::objects["Camera"].draw();
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
