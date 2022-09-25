#include "model.h"
#include <glm/glm/fwd.hpp>
#include <glm/glm/glm.hpp>



std::map<std::string, Model> Model::models; // singleton
Model Model::init(std::string mesh_filepath)
{

	std::vector<glm::vec2> pos_vtx;
	std::vector<GLushort> idx_vtx;
	GLushort f;
	GLushort ix, iy, iz;
	GLfloat x, y;
	Model result;
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