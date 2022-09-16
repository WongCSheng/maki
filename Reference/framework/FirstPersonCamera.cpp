#include "FirstPersonCamera.h"
#include "script_common.h"
#include <iostream>
#include "Window.h"

FirstPersonCamera::FirstPersonCamera()
{
}


FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::CameraInit(Vector3 position, Vector3 forward, Vector3 up)
{
	this->position = position;
	this->forward = forward;
	this->up = up;

	//TargetUpdate();
	onMouse(Window::getInstance()->Width() * 0.5, Window::getInstance()->Height() * 0.5);
}

void FirstPersonCamera::onMouse(double x, double y)
{
	MouseCursorCalc(x, y);

	MouseControl();

	TargetUpdate();
}

void FirstPersonCamera::Update(const double dt)
{
	owner->transform->SetPosition(position);
	owner->transform->SetForward(forward); // To Do

	Vector3 movingDir = forward;
	movingDir.y = 0;
	movingDir.Normalize();

	Vector3 right = movingDir.Cross(up);
	right.y = 0;

	if (Input.GetKeyDown(KEY_W))
	{
		position += movingDir * (float)dt * CAMERA_MOVING_SPEED;
	}

	if (Input.GetKeyDown(KEY_A))
	{
		position -= right * (float)dt * CAMERA_MOVING_SPEED;
	}

	if (Input.GetKeyDown(KEY_S))
	{
		position -= movingDir * (float)dt * CAMERA_MOVING_SPEED;
	}

	if (Input.GetKeyDown(KEY_D))
	{
		position += right * (float)dt * CAMERA_MOVING_SPEED;
	}

	TargetUpdate();
}

void FirstPersonCamera::TargetUpdate(void)
{
	target = (forward * ZOOM_DISTANCE) + position;
}