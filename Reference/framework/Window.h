#ifndef WINDOW_H
#define WINDOW_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	static inline Window* getInstance(void)
	{
		if (s_instance == 0)
		{
			s_instance = new Window();
		}
		return s_instance;
	}

	GLFWwindow* window;

	void SetUp();
	int Width();
	int Height();

private:
	Window();
	~Window();

	int width, height;

	int monWidth, monHeight;

	int m_posX, m_posY;

	GLFWmonitor* myMonitor;

	const GLFWvidmode* myMode;

	const char* title;

	void InitMonitor();
	void InitWindowHint();
	void CreateWindow();

	static Window* s_instance;
};

#endif