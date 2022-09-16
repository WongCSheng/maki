#include "Input.h"

Input* Input::instance = 0;
Input::Input()
{
	for (int i = 32; i <= 122; ++i)
	{
		keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(i)][KEY_STATE_PRESS] = false;
		keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
	}

	for (int i = 256; i <= 269; ++i)
	{
		keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(i)][KEY_STATE_PRESS] = false;
		keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
	}

	for (int i = 290; i <= 299; ++i)
	{
		keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(i)][KEY_STATE_PRESS] = false;
		keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
	}
}


Input::~Input()
{
	keys.clear();
}

void Input::Update(const KEY key, const KEY_STATE action)
{
	if (keyqueue.size() > 0)
	{
		keys[keyqueue.front()][KEY_STATE_RELEASE] = false;
		keyqueue.pop();
	}

	if (action != KEY_STATE_RELEASE)
	{
		keys[key][action] = true;
		keyqueue.push(key);
	}
	else
	{
		keys[key][KEY_STATE_PRESS] = false;
		keys[key][KEY_STATE_REPEAT] = false;
	}
}

bool Input::GetKey(const KEY key, const KEY_STATE action)
{
	return keys[key][action];
}

bool Input::GetKeyDown(const KEY key)
{
	if (keys[key][KEY_STATE_PRESS] || keys[key][KEY_STATE_REPEAT])
	{
		return true;
	}
	return false;
}