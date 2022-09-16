#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "ICallbacks.h"

#include <vector>

using namespace std;

class Entity;
class SceneBase : public ICallback
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init(void) = 0;
	virtual void Run(double dt);
	virtual void Update(double dt);
	virtual void Render(void);

	vector<Entity*> entities;
	bool exit;
};

#endif