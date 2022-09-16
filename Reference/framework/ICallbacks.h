#ifndef ICALLBACK_H
#define ICALLBACK_H

#include "Keys.h"

class ICallback
{
public:
	virtual void KeyboardCB(KEY Key, KEY_STATE action) {};

	virtual void MouseCursorCB(double x, double y) {};

	virtual void MouseButtCB(KEY Key, KEY_STATE action) {};

	virtual void MouseCursorEnterCB(bool enter) {};

	virtual void MouseScrollCB(double xoffset, double yoffset) {};

	virtual void WindowResizeCB(int width, int height) {};

	virtual void WindowPosCB(int x, int y) {};

	virtual void WindowIconifyCB(int i) {};

	virtual void WindowShldCloseCB(int i) {};

	virtual void WindowFocusCB(int focused){};
};

#endif