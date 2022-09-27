#include "../include/common_headers.hpp"

Input* Input::instance = 0;



void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == KEY::KEY_E && action == GLFW_PRESS)
	{
		std::cout << "Key E is pressed" << std::endl;
	
	}
	if (action == GLFW_PRESS)
	{
		
		Input::Instance().keys[static_cast<KEY>(key)].operator[](KEY_STATE::KEY_STATE_PRESS) = true;
		std::cout << "Any key is pressed" << std::endl;

	}
}

//constructor to load all the keys
Input::Input()
{
	//loop through all keys in ASCII character, set them to default false state(key not pressed)
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

//key destructor
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

//return true when checking a key is pressed
bool Input::GetKey(const KEY key, const KEY_STATE action)
{
	return keys[key][action];
}

//check if a key is held down
bool Input::GetKeyDown(const KEY key)
{
	if (keys[key][KEY_STATE_PRESS] || keys[key][KEY_STATE_REPEAT])
	{
		return true;
	}
	return false;
}