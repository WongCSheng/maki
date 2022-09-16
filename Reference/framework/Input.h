#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <queue>
#include "Keys.h"

class Input
{
public:
	static Input& Instance()
	{
		if (instance != 0)
		{
			return *instance;
		}
		instance = new Input();
		return *instance;
	}

	void Update(const KEY key, const KEY_STATE action);
	bool GetKey(const KEY key, const KEY_STATE action);
	bool GetKeyDown(const KEY key);

private:
	Input();
	~Input();

	static Input* instance;
	std::map<KEY, std::map<KEY_STATE, bool>> keys;
	std::queue<KEY> keyqueue;
};

#endif