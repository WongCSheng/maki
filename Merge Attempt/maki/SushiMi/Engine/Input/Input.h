#ifndef INPUT_H
#define INPUT_H

#include "../Headers/STL_Header.h"
#include "Keys.h"
#include <glfw/include/GLFW/glfw3.h>
#include "../Engine/System/SystemFrame.h"

namespace Core
{
	class Input : public SystemFrame
	{
	public:
		/*static Input& Instance()
		{
			if (instance != 0)
			{
				return *instance;
			}
			instance = new Input();
			return *instance;
		}*/

		Input();
		~Input();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		void UpdateInput(const KEY key, const KEY_STATE action);
		bool GetKey(const KEY key, const KEY_STATE action);
		bool GetKeyDown(const KEY key);
		void GetMouse(GLFWwindow* window, int action);

	private:
		/*Input();
		~Input();*/

		//static Input* instance;
		std::map<KEY, std::map<KEY_STATE, bool>> keys;
		std::queue<KEY> keyqueue;
	};
}
#endif