#include "Input.h"

namespace Core
{
	//Input* Input::instance = 0;

	//constructor to load all the keys
	Input::Input()
	{
		//loop through all keys in ASCII character, set them to default false state(key not pressed)
		for (int i = 0; i <= 86; ++i)
		{
			keys[(KEY)(i)][KEY_STATE_RELEASE] = false;
			keys[(KEY)(i)][KEY_STATE_PRESS] = false;
			keys[(KEY)(i)][KEY_STATE_REPEAT] = false;
		}

		keys[(KEY)(999)][KEY_STATE_RELEASE] = false;
		keys[(KEY)(999)][KEY_STATE_PRESS] = false;
		keys[(KEY)(999)][KEY_STATE_REPEAT] = false;
	}

	//key destructor
	Input::~Input()
	{
		keys.clear();
	}

	void Input::Init()
	{
	}

	void Input::Update(const double dt)
	{
	}

	void Input::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{
	}

	void Input::UpdateInput(const KEY key, const KEY_STATE action)
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

	void Input::GetMouse(GLFWwindow* window, int action)
	{
		if (/*mouse == MOUSE_BUTTON_LEFT &&*/ action == KEY_STATE_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, & ypos);
			std::cout << "Coursor position at " << xpos << " : " << ypos;
		}
	}
}