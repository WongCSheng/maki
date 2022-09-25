/*!
@file		glapp.cpp
@author		pghali@digipen.edu
@co-author  louishetong.wang@digipen.edu
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
// define singleton containers
std::map<std::string, GLSLShader>		GLApp::shdrpgms;
std::map<std::string, GLApp::GLModel>	GLApp::models;
std::map<std::string, GLApp::GLObject>	GLApp::objects;
GLApp::Camera2D GLApp::camera2d;
GLApp::GLObject temp;
GLboolean first_person_cam = GL_FALSE;
/*  _________________________________________________________________________ */
/*! init
@param none
@return none

Initialize color, viewports, VAO and create shader program
*/
void GLApp::init() {
	/////////////////////// initialize openGL//////////////////////////////////
	// Part 1: clear colorbuffer with RGBA value in glClearColor ...

	glClearColor(1.0, 1.0, 1.0, 1.0);

	// part 2: use entire window as viewport
	GLint w{ GLHelper::width }, h{ GLHelper::height };

	glViewport(0, 0, w, h);

	GLApp::vps.push_back({ 0, 0, 0, 0 });
	GLViewport{ vps[0].x, vps[0].y, vps[0].width, vps[0].height };

	// part 3: parse scene file $(SolutionDir)scenes/tutorial-4.scn
	// and store repo of models of type GLModel in container GLApp::models,
	// store shader programs of type GLSLShader in container GLApp::shdrpgms,
	// and store repo of objects of type GLObject in container GLApp::objects
	GLApp::init_scene("../scenes/tutorial-4.scn");

	//Part 4: Initialize camera
	GLApp::camera2d.init(GLHelper::ptr_window, &GLApp::objects.at("Camera"));

	//Part 5: Print OpenGL context and GPU specs
}


/*  _________________________________________________________________________ */
/*! insert_shdrpgm
@param none
@return none

insert shader program into container GLApp::shdrpgms
*/
static void insert_shdrpgm(std::string shdr_pgm_name, std::string vtx_shdr, std::string frg_shdr)
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
		GLApp::GLObject currObj;
		getline(ifs, line); // 1st parameter: model's name
		std::istringstream line_modelname{ line };
		std::string model_name;
		line_modelname >> model_name;

		//find model with the same name
		std::map<std::string, GLApp::GLModel>::iterator mdl_iterator;
		mdl_iterator = models.find(model_name);

		if (mdl_iterator == GLApp::models.end())
		{
			GLApp::GLModel curr_mdl;
			if (model_name == "circle")
			{
				mesh_path = "../meshes/circle.msh";
				curr_mdl.primitive_type = GL_TRIANGLE_FAN;
			}
			else if (model_name == "square")
			{
				mesh_path = "../meshes/square.msh";
				curr_mdl.primitive_type = GL_TRIANGLES;
			}
			else if (model_name == "triangle")
			{
				mesh_path = "../meshes/triangle.msh";
				curr_mdl.primitive_type = GL_TRIANGLES;
			}
			curr_mdl = curr_mdl.init(mesh_path);
			models.insert(std::pair<std::string, GLApp::GLModel>(model_name, curr_mdl));
			mdl_iterator = models.find(model_name);
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

		getline(ifs, line); // 6th parameter: orientation factors of object: initial angular orientation (where am i looking at start up?)
		std::istringstream line_orientation{ line };
		GLfloat orientation_x, orientation_y;
		line_orientation >> orientation_x >> orientation_y;
		currObj.orientation = { orientation_x, orientation_y };

		getline(ifs, line); // 7th factor: Obj's position in game world.
		std::istringstream line_pos{ line };
		GLfloat pos_x, pos_y;
		line_pos >> pos_x >> pos_y;
		currObj.position = { pos_x, pos_y };

		currObj.mdl_ref = mdl_iterator;
		currObj.shd_ref = shdr_iterator;

		objects.insert(std::pair<std::string, GLApp::GLObject>(object_name, currObj));

	}

}

/*  _________________________________________________________________________ */
/*! GLModel init(std::string)
@param std::string
@return GLModel result

initialize the 3 different types of models by reading from the filepath and storing the data into a model.
*/
GLApp::GLModel GLApp::GLModel::init(std::string mesh_filepath)
{

	std::vector<glm::vec2> pos_vtx;
	std::vector<GLushort> idx_vtx;
	GLushort f;
	GLushort ix, iy, iz;
	GLfloat x, y;
	GLModel result;
	std::string model_name;
	std::ifstream ifs{ mesh_filepath, std::ios::in };
	if (!ifs)
	{
		std::cout << "ERROR: Unable to open mesh file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	ifs.seekg(0, std::ios::beg);
	while (ifs.peek() != EOF)
	{
		std::string line;
		getline(ifs, line);
		std::istringstream prefix_check{ line };
		char prefix;
		prefix_check >> prefix;
		switch (prefix)
		{
		case 'n':
			prefix_check >> model_name;
			break;

		case 'v':
			prefix_check >> x >> y;
			pos_vtx.emplace_back(x, y);
			break;
		case 'f':
			result.primitive_type = GL_TRIANGLE_FAN;
			if (idx_vtx.size() == 0)
			{
				prefix_check >> ix >> iy >> iz;
				idx_vtx.emplace_back(ix);
				idx_vtx.emplace_back(iy);
				idx_vtx.emplace_back(iz);
			}
			else
			{
				prefix_check >> f;
				idx_vtx.emplace_back(f);
			}
			break;
		case 't':
			result.primitive_type = GL_TRIANGLES;
			prefix_check >> ix >> iy >> iz;
			idx_vtx.emplace_back(ix);
			idx_vtx.emplace_back(iy);
			idx_vtx.emplace_back(iz);
			break;
		}

	}
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);
	glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), NULL, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());

	GLuint vaoid;
	glCreateVertexArrays(1, &vaoid);
	glEnableVertexArrayAttrib(vaoid, 0);
	glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 0, 0);
	glBindVertexArray(0);

	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(),
		reinterpret_cast<GLvoid*>(idx_vtx.data()),
		GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);

	result.vaoid = vaoid;
	result.draw_cnt = idx_vtx.size();
	return result;
}

/*  _________________________________________________________________________ */
/*! GLApp::Camera2D::init(GLFWwindow* pWindow, GLApp::GLObject* ptr)
@param GLFWwindow* pWindow, GLApp::GLObject* ptr
@return none

Assign pgo to camera and compute aspect ratio, initialize as free camera.
*/
void GLApp::Camera2D::init(GLFWwindow* pWindow, GLApp::GLObject* ptr)
{
	// assign address of object of type GLApp::GLObject with name "Camera" in objects
	pgo = &GLApp::objects.at("Camera");

	// compute camera window's aspect ratio
	GLsizei fb_width, fb_height;
	glfwGetFramebufferSize(pWindow, &fb_width, &fb_height);
	ar = static_cast<GLfloat>(fb_width) / static_cast<GLfloat>(fb_height);

	// compute camera's up and right vectors
	up = { -sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(M_PI)), cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(M_PI)) };
	right = { cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(M_PI)), sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(M_PI)) };

	// at startup, camera must be initialized to free camera
	view_xform =
	{
		{1, 0, 0},
		{0, 1, 0},
		{-pgo->position.x, -pgo->position.y, 1}
	};

	GLfloat cam_W = ar * GLHelper::height;
	GLfloat cam_H = ar * GLHelper::width;
	// compute other matrices
	camwin_to_ndc_xform =
	{
		{2 / cam_W, 0, 0},
		{0, 2 / cam_H, 0},
		{0, 0, 1}
	};
	world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
}

/*  _________________________________________________________________________ */
/*! GLApp::GLObject::update(GLdouble delta_time)
@param GLDouble delta_time
@return none

All the transformation matrix scale,rot, trans and model to ndc transformation.
*/
void GLApp::GLObject::update(GLdouble delta_time)
{
	const glm::mat3 scale_mat
	{
		{scaling.x, 0, 0},
		{0, scaling.y, 0},
		{0, 0, 1}
	};

	orientation.x += orientation.y * static_cast<GLfloat>(GLHelper::delta_time);
	const GLfloat radians = orientation.x / 180.f * static_cast<GLfloat>(M_PI);

	const glm::mat3 rot_mat
	{
		{cos(radians), sin(radians), 0},
		{-sin(radians), cos(radians), 0},
		{0, 0, 1}
	};
	const glm::mat3 trans_mat
	{
		{1, 0, 0},
		{0, 1, 0},
		{position.x, position.y, 1}
	};


	mdl_to_ndc_xform = GLApp::camera2d.world_to_ndc_xform * (trans_mat * rot_mat * scale_mat);

}

/*  _________________________________________________________________________ */
/*! GLApp::Camera2D::update(GLFWwindow*)
@param GLFWwindow*
@return none

Update camera's ratio, orientation, position, up and right vectors, zoom and transformation matrices
*/
void GLApp::Camera2D::update(GLFWwindow*)
{
	ar = (GLfloat)GLHelper::width / (GLfloat)GLHelper::height;
	// update POV
	if (camtype_flag == GL_TRUE)
	{
		if (first_person_cam == GL_FALSE)
		{
			first_person_cam = GL_TRUE;
		}
		else if (first_person_cam == GL_TRUE)
		{
			first_person_cam = GL_FALSE;
		}
		camtype_flag = GL_FALSE;
	}

	if (first_person_cam == GL_TRUE)
	{
		view_xform = { {right.x,up.x,0.f},
						{right.y,up.y,0.f},
						{glm::dot(-glm::normalize(right),pgo->position),glm::dot(-glm::normalize(up),pgo->position),1.f}
		};
	}
	else if (first_person_cam == GL_FALSE)
	{
		view_xform = { {1.f,0.f,0.f},
						{0.f,1.f,0.f},
						{-pgo->position.x,-pgo->position.y,1.f}
		};
	}
	if (left_turn_flag == GL_TRUE)
	{
		pgo->orientation.x += pgo->orientation.y;
	}
	if (right_turn_flag == GL_TRUE)
	{
		pgo->orientation.x -= pgo->orientation.y;
	}
	// update camera's up and right vectors (if required)

	up = { -sinf(glm::radians(pgo->orientation.x)),
			cosf(glm::radians(pgo->orientation.x)) };

	right = { cosf(glm::radians(pgo->orientation.x)),
				sinf(glm::radians(pgo->orientation.x)) };

	// update camera's position (if required) 
	if (move_flag == GL_TRUE)
	{
		pgo->position += (linear_speed * glm::normalize(up));//displace the camera
	}

	// implement camera's zoom effect (if required)
	if (zoom_flag == GL_TRUE)
	{
		if (height <= min_height)
		{
			height_chg_dir = 1;
		}
		else if (height >= max_height)
		{
			height_chg_dir = -1;
		}
		height += (height_chg_dir * height_chg_val);
	}


	// compute window-to-NDC transformation matrix
	// compute other matrices ...
	camwin_to_ndc_xform = { {2.0f / (height * ar),0.f,0.f},
							{0.f,2.f / height,0.f},
							{0.f,0.f,1.f}
	};
	GLfloat radians = glm::radians(camera2d.pgo->orientation.x);

	glm::mat3 rot_mat
	{
			{cos(radians), sin(radians), 0},
			{-sin(radians), cos(radians), 0},
			{0, 0, 1}
	};

	glm::mat3 scale_mat
	{
		{camera2d.pgo->scaling.x, 0, 0},
		{0, camera2d.pgo->scaling.y, 0},
		{0, 0, 1}
	};

	glm::mat3 trans_mat
	{
		{1, 0, 0},
		{0, 1, 0},
		{camera2d.pgo->position.x, camera2d.pgo->position.y, 1}
	};
	glm::mat3 model_mtx = trans_mat * rot_mat * scale_mat;
	camera2d.pgo->mdl_to_ndc_xform = world_to_ndc_xform * model_mtx;
	// compute world-to-NDC transformation matrix
	world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
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
	camera2d.update(GLHelper::ptr_window);

	// next, iterate thru each element in container object
	// for each object of type GLObject, call update function
	// except for camera
	for (auto& x : GLApp::objects)
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
	ss << "Tutorial 4 | Wang He Tong Louis | ";
	ss << std::fixed << std::setprecision(2) << " Camera Position: (" << camera2d.pgo->position.x << ", ";
	ss << camera2d.pgo->position.y << ") | ";
	ss << std::fixed << std::setprecision(0) << " Orientation: " << camera2d.pgo->orientation.x << " | ";
	ss << " Window height: " << GLApp::camera2d.height << " | ";
	ss << std::fixed << std::setprecision(2) << GLHelper::fps;
	glfwSetWindowTitle(GLHelper::ptr_window, ss.str().c_str());

	// clear back buffer as before ...
	glClear(GL_COLOR_BUFFER_BIT);

	// draw everything before rendering camera
	for (auto const& x : GLApp::objects)
	{
		if (x.first != "Camera")
		{
			x.second.draw();
		}
	}
	GLApp::objects["Camera"].draw();
}

/*  _________________________________________________________________________ */
/*! GLApp::GLObject::draw() const
@param
@return none

load shader program, bind VAO, copy color to fragment shader, copy model to vertex shader, call glDrawElements
unbind VAO and unload shader program
*/
void GLApp::GLObject::draw() const
{
	// load shader program
	GLApp::shdrpgms[shd_ref->first].Use();

	// bind VAO of object's model
	glBindVertexArray(GLApp::models[mdl_ref->first].vaoid);

	// copy obj color to uColor
	shdrpgms[shd_ref->first].SetUniform("uColor", color);

	// copy model to ndc matrix to uModelToNDC
	shdrpgms[shd_ref->first].SetUniform("uModel_to_NDC", mdl_to_ndc_xform);

	// call glDrawElements with appropriate arguments
	glDrawElements(models[mdl_ref->first].primitive_type, models[mdl_ref->first].draw_cnt, GL_UNSIGNED_SHORT, NULL);

	glBindVertexArray(0);
	GLApp::shdrpgms[shd_ref->first].UnUse();
}

/*  _________________________________________________________________________ */
/*! cleanup
@param none
@return none

empty for now
*/
void GLApp::cleanup() {
	// empty for now
}
