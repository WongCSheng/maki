#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include "Camera.h"
class FirstPersonCamera :
	public Camera
{
public:
	FirstPersonCamera();
	virtual ~FirstPersonCamera();

	virtual void CameraInit(Vector3 position, Vector3 forward, Vector3 up);
	//virtual void onKeyBoard(KEY key, KEY_STATE action, const float& dt);
	virtual void onMouse(double x, double y);

	virtual void Update(const double dt);
	void TargetUpdate(void);
};

#endif