#pragma once

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "../Engine/System/SystemFrame.h"


namespace Core
{
	/*forward declaration*/
	class Player;
	class Sprite;
	//extern Player* player;
	class ObjectFactory;

	class Window : public SystemFrame
	{
	public:
		Window(int width, int height);

		~Window();

		void Init() {}
		void Update(const double dt) {}
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer) {}

		void Input();

		void Resize();

		void Mainloop();

		static inline void ImGuiToObjContainer(ObjectFactory*);

		static inline Player* player;
		static inline GLFWwindow* window_ptr; //moved from private to public for access in main.cpp
		static inline Sprite* obj;
		static inline Sprite* sp;
		static inline Sprite* ingredient;
		static inline Sprite* goal;
		static inline Sprite* trap;
	
		static inline struct ScreenDimensions {
			static inline int screenwidth;
			static inline int screenheight;
		};

	private:
		int m_width, m_height;
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