#pragma once

#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

namespace Core
{
	/*forward declaration*/
	class Player;
	class Sprite;

	class Window
	{
	public:
		Window(int width, int height);

		~Window();

		void Input();

		void Resize();

		void Mainloop();

		static inline Player* player;
		static inline GLFWwindow* window_ptr; //moved from private to public for access in main.cpp
		static inline Sprite* sp;
		static inline Sprite* sp1;
	
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
}