#pragma once

#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

/*forward declaration*/
class Player;
class Sprite;




extern Player* player;

class Window
{
public:
	Window(int width, int height);

	~Window();

	void Input();

	void Resize();

	void Mainloop();


	static inline Player* player;
	static Sprite* sp;
	static Sprite* sp1;
	inline static GLFWwindow* window_ptr; //moved from private to public for access in main.cpp
	
	static inline struct ScreenDimensions {
		static inline int screenwidth;
		static inline int screenheight;
	};
private:
	int m_width, m_height;
	GLFWwindow* ptr_win;
	double starttime, endtime, delta;
};

class pseudomain
{
public:
	static void draw();
	static void update();
	static void init();
	static void cleanup();

};