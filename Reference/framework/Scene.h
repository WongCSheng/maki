#ifndef SCENE_H
#define SCENE_H

#include "SceneBase.h"

#include <vector>

using namespace std;

class Graphics;
class Entity;
class Camera;
class DirectionLight;
class PointLight;
class RendererSystem;
class TransformSystem;
class CameraSystem;
class LightSystem;
class Scene :
	public SceneBase
{
public:
	Scene();
	virtual ~Scene();

	virtual void KeyboardCB(KEY Key, KEY_STATE action);
	virtual void MouseCursorCB(double x, double y);
	virtual void MouseCursorEnterCB(bool enter);
	virtual void WindowFocusCB(int focused);

	virtual void Init(void);
	void Run(double dt);
	virtual void Update(double dt);
	virtual void Render(void);

private:
	Graphics *graphics;
	Camera* CurrentCamera;
	vector<Entity*> testEntities;
	float tempCounter;

	int focused;
	bool enter;
};

#endif