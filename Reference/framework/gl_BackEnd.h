#ifndef GL_BACKEND_H
#define GL_BACKEND_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class ICallback;

class gl_BackEnd
{
public:
	void GLBackEndRun(ICallback* pCallBack);
	void GLSwapBuffers(void);
	void GLPollEvents(void);
	void GLFWBackEndTerminate(void);

	static inline gl_BackEnd* getInstance(void)
	{
		if (s_instance == NULL)
		{
			s_instance = new gl_BackEnd();
		}
		return s_instance;
	}

	static inline bool exist(void)
	{
		return s_instance != 0;
	}

private:
	gl_BackEnd(void);
	~gl_BackEnd(void);

	void initAllCB(void);
	static gl_BackEnd* s_instance;
};

#endif