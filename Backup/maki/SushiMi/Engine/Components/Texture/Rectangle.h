#pragma once
#include <../glew/include/GL/glew.h>
// singlton pattern 

struct Rect
{
	unsigned int VAO;  //vertex array object
	unsigned int VBO;  // vertex buffer object
	unsigned int CBO;  // color buffer object
	unsigned int UVBO; // uv buffer object
};

class RectangleSystem
{
public:
	static RectangleSystem* GetInstance();

	Rect Generate();

	void Delete(Rect& obj);

private:
	RectangleSystem();

	static RectangleSystem* _instance;
};