#include "gl_BackEnd.h"
#include "ICallbacks.h"
#include <iostream>
#include "Window.h"

static ICallback* s_pCallBack = NULL;
gl_BackEnd* gl_BackEnd::s_instance = NULL;

gl_BackEnd::gl_BackEnd(void)
{
}


gl_BackEnd::~gl_BackEnd(void)
{
}

static void KeyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_pCallBack->KeyboardCB((KEY)key, (KEY_STATE)action);
}

static void PassiveMouseCB(GLFWwindow* window, double x, double y)
{
	s_pCallBack->MouseCursorCB(x, y);
}

static void MouseCB(GLFWwindow* window, int key, int action, int mods)
{
	s_pCallBack->MouseButtCB((KEY)key, (KEY_STATE)action);
}

static void CursorEnterCB(GLFWwindow* window, int enter)
{
	glfwSetCursorPos(window, Window::getInstance()->Width() >> 1, Window::getInstance()->Height() >> 1);
	s_pCallBack->MouseCursorEnterCB(enter == 0 ? true : false);
}

static void MouseScrollCB(GLFWwindow* window, double xOffSet, double yOffSet)
{
	s_pCallBack->MouseScrollCB(xOffSet, yOffSet);
}

static void WindowFocusCB(GLFWwindow* window, int focused)
{
	s_pCallBack->WindowFocusCB(focused);
}

void gl_BackEnd::GLBackEndRun(ICallback* pCallBack) //pCallBack is scene1 itself
{
	s_pCallBack = pCallBack;
	initAllCB();
}

void gl_BackEnd::GLSwapBuffers(void)
{
	glfwSwapBuffers(Window::getInstance()->window);
}

void gl_BackEnd::GLPollEvents(void)
{
	glfwPollEvents();
}

void gl_BackEnd::GLFWBackEndTerminate(void)
{
	glfwDestroyWindow(Window::getInstance()->window);
	glfwTerminate();
}

void gl_BackEnd::initAllCB(void)
{
	GLFWwindow* window = Window::getInstance()->window;

	glfwSetKeyCallback(window, KeyboardCB);
	glfwSetMouseButtonCallback(window, MouseCB);
	glfwSetCursorPosCallback(window, PassiveMouseCB);
	glfwSetCursorEnterCallback(window, CursorEnterCB);
	glfwSetScrollCallback(window, MouseScrollCB);
	glfwSetWindowFocusCallback(window, WindowFocusCB);
}
