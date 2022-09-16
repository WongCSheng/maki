#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"
#include "Keys.h"
#include "Vector3.h"
#include "Matrix4f.h"
#include "Quaternion.h"

class Camera : public Component
{
	friend class CameraSystem;
public:
	Camera();
	virtual ~Camera() = 0;

	virtual void CameraInit(Vector3, Vector3, Vector3) = 0;
	//virtual void onKeyBoard(KEY key, KEY_STATE action, const float& dt);
	virtual void onMouse(double x, double y) = 0;

	void Update(const double dt);
	void LastMousePosUpdate(double x, double y);
	void MouseCamZoom(double xoffset, double yoffset, const double dt);
	Matrix4f ViewMat(void);
	Matrix4f GetTransformMat(void);

public:
	Vector3 position, target, up, vel, forward;

	Quaternion q;

	float MOUSE_SENSITIVITY, CAMERA_MOVING_SPEED;
	float ZOOM_DISTANCE, ZOOM_SPEED, ZOOM_IN_LIMIT, ZOOM_OUT_LIMIT, PITCH_LIMIT;
	float pitch, yaw, l_pitch, l_yaw, turningAngle, tiltingAngle;
	double near, far, fov;

protected:
	void MouseCursorCalc(double x, double y);
	void MouseControl(void);

	Matrix4f view;

private:
	void LookUpAndDown(float a);
	void TurnLeftAndRight(float a);

	double mouse_diff_x, mouse_diff_y, mouse_last_x, mouse_last_y;
};

#endif