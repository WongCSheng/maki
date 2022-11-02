/*!************************************
\file		graphicsSerializer.cpp
\author		thea.sea, thea.sea@digipen.edu (for graphics object serializing)
\co-author	aurelia.chong (for AABB calculations)
\brief		function to initialize the graphics scene from a .txt file
**************************************/
#include "../include/common_headers.hpp"

void sceneInitializer(std::string scene_filename)
{
	std::ifstream ifs{ scene_filename, std::ios::in };
	if (!ifs)
	{
		std::cout << "ERROR: Unable to open scene file: " << scene_filename << std::endl;
		exit(EXIT_FAILURE);
		assert("ERROR: Unable to open scene file: ", (!ifs) );	
	}
	ifs.seekg(0, std::ios::beg);

	std::string line;
	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore very first line
	getline(ifs, line); // first line is count of objects in scene
	std::istringstream line_sstm{ line };
	int obj_cnt;
	line_sstm >> obj_cnt; // read count of objs in scene

	std::vector<std::string> ObjVector;
	while (obj_cnt--) // read each object's param, each newline is an obj
	{
		std::string mesh_path;
		Object currObj;

		getline(ifs, line); // second line is data

		std::istringstream line_sstm{ line };

		std::string word;
		while (line_sstm >> word) //make every string a parameter
		{
			//std::cout << word << std::endl; // 1st eg: takes "square"
			ObjVector.push_back(word);
		}
		for (int i = 0; i < ObjVector.size(); i += 14)
		{
			//1st param: name of model
			std::istringstream line_modelname{ ObjVector[i] };
			std::string model_name;
			line_modelname >> model_name;
			//find model with the same name
			std::map<std::string, Model>::iterator mdl_iterator;
			mdl_iterator = Model::models.find(model_name);

			bool hasMass = false;

			if (mdl_iterator == Model::models.end())
			{
				Model curr_mdl;
				
				if (model_name == "square")
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
				else if (model_name == "circle")
				{
					mesh_path = "../mesh/circle.msh";
					curr_mdl.primitive_type = GL_TRIANGLE_FAN;
					//hasMass = true;
					//currObj.status = true; //alive

				}
				curr_mdl = curr_mdl.init(mesh_path);
				Model::models.insert(std::pair<std::string, Model>(model_name, curr_mdl));
				mdl_iterator = Model::models.find(model_name);
			}

			//2nd param: Given Object Name
			std::string object_name{ ObjVector[i + 1] };
			
			//3rd param: R of RGB
			GLfloat red{ std::stof(ObjVector[i + 2]) };

			//4th param: G of RGB
			GLfloat green{ std::stof(ObjVector[i + 3]) };

			//5th param: B of RGB
			GLfloat blue{ std::stof(ObjVector[i + 4]) };
			currObj.color = { red, green, blue };

			//6th param: x scale
			GLfloat scale_x{ std::stof(ObjVector[i + 5]) };

			//7th param: y scale
			GLfloat scale_y{ std::stof(ObjVector[i + 6]) };
			currObj.scaling = { scale_x, scale_y };

			//8th param: x_orientation
			GLfloat orientation_x{ std::stof(ObjVector[i + 7]) };

			//9th param: y_orientation
			GLfloat orientation_y{ std::stof(ObjVector[i + 8]) };
			currObj.orientation = { orientation_x, orientation_y };

			//10th x pos
			GLfloat pos_x{ std::stof(ObjVector[i + 9]) };

			//11th y pos
			GLfloat pos_y{ std::stof(ObjVector[i + 10]) };
			currObj.position = { pos_x, pos_y };


			currObj.position = { pos_x, pos_y };
			currObj.initialPos = { currObj.position };			//stores initial position for distance calculation

				/* construct AABB box */
			if (model_name == "square")
			{
				currObj.aabb.min.x = currObj.position.x - (currObj.scaling.x / 2); //calculating bottom left min.x
				currObj.aabb.min.y = currObj.position.y - (currObj.scaling.y / 2); //calculating bottom left min.y
				currObj.aabb.max.x = currObj.position.x + (currObj.scaling.x / 2); //calculating top right max.x
				currObj.aabb.max.y = currObj.position.y + (currObj.scaling.y / 2); //calculating top right max.y
			}
			else if (model_name == "circle")
			{
				currObj.aabb.min.x = currObj.position.x - (currObj.scaling.x); //calculating bottom left min.x
				currObj.aabb.min.y = currObj.position.y - (currObj.scaling.y); //calculating bottom left min.y
				currObj.aabb.max.x = currObj.position.x + (currObj.scaling.x); //calculating top right max.x
				currObj.aabb.max.y = currObj.position.y + (currObj.scaling.y); //calculating top right max.y
			}			
			

			//12th param: shader program name
			std::string shdr_name{ ObjVector[i + 11] };

			//13th param: vert shader path
			std::string shdr_vert{ ObjVector[i + 12] };

			//14th param: frag shader path
			std::string shdr_frag{ ObjVector[i + 13] };
			
			std::map<std::string, GLSLShader>::iterator shdr_iterator;
			shdr_iterator = GLApp::shdrpgms.find(shdr_name);
			if (shdr_iterator == GLApp::shdrpgms.end())
			{
				GLApp::insert_shdrpgm(shdr_name, shdr_vert, shdr_frag);
				shdr_iterator = GLApp::shdrpgms.find(shdr_name);
			}
			
			// GLApp::insert_shdrpgm(shdr_name, shdr_vert, shdr_frag);
			//std::cout << "current object name: " << object_name << "Min " << currObj.aabb.min.x << " " << currObj.aabb.min.y << std::endl;
			//std::cout << "current object name: " << object_name << "Max " << currObj.aabb.max.x << " " << currObj.aabb.max.y << std::endl;
			//std::cout << "Object position(x,y) " << currObj.position.x << " " << currObj.position.y << std::endl;
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

			currObj.mdl_ref = mdl_iterator;
			currObj.shd_ref = shdr_iterator;
			//currObj.shd_ref = GLApp::shdrpgms.find(shdr_name);
			Object::objects.insert({ object_name, currObj });
		}
	}
}
