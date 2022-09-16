#include "Camera.h"
#include "Transform.h"
#include <iostream>
#include "Window.h"
#include "Entity.h"

Camera::Camera(void) : 
MOUSE_SENSITIVITY(5.f), 
CAMERA_MOVING_SPEED(20.f),
ZOOM_DISTANCE(5.f), 
ZOOM_SPEED(100.f), 
ZOOM_IN_LIMIT(5.f), 
ZOOM_OUT_LIMIT(2250.f), 
PITCH_LIMIT(85.000f),
pitch(0.f), yaw(0.f), l_pitch(0.f), l_yaw(0.f), turningAngle(0.f), tiltingAngle(0.f), fov(50.0),
mouse_diff_x(0.0), mouse_diff_y(0.0), mouse_last_x(Window::getInstance()->Width() * 0.5), mouse_last_y(Window::getInstance()->Height() * 0.5),
near(0.1),
far(2000.0)
{
	
}

Camera::~Camera()
{
}

void Camera::LastMousePosUpdate(double x, double y)
{
	//Store the current position as the last position;
	mouse_last_x = x;
	mouse_last_y = y;
}

void Camera::MouseCamZoom(double xoffset, double yoffset, const double dt)
{
	//For zooming in

	if (yoffset > 0 || yoffset < 0)
	{
		ZOOM_DISTANCE -= (float)(ZOOM_SPEED * yoffset * dt);
	}

	/*if (fov >= ZOOM_IN_LIMIT && fov <= ZOOM_OUT_LIMIT)
	{
		fov -= ZOOM_SPEED * dt;
	}

	if (fov <= ZOOM_IN_LIMIT)
	{
		fov = ZOOM_IN_LIMIT;
	}

	if (fov >= ZOOM_OUT_LIMIT)
	{
		fov = ZOOM_OUT_LIMIT;
	}*/
}

Matrix4f Camera::ViewMat(void)
{
	view.SetToIdentity();

	view.SetToLookAt(position.x, position.y, position.z, target.x, target.y, target.z, up.x, up.y, up.z);

	return view;
}

Matrix4f Camera::GetTransformMat(void)
{
	return owner->transform->TransformMat();
}

void Camera::MouseCursorCalc(double x, double y)
{
	//Calculate the difference in positions
	mouse_diff_x = x - mouse_last_x;
	mouse_diff_y = y - mouse_last_y;

	//Calculate the yaw and pitch
	l_yaw = static_cast<float>(mouse_diff_x)* 0.0174555555555556f; // * 3.142f/180.f
	l_pitch = static_cast<float>(mouse_diff_y)* 0.0174555555555556f; // * 3.142f/180.f

	LastMousePosUpdate(x, y);
}

void Camera::MouseControl(void)
{
	//For left and right
	if (l_yaw != 0.000f)
	{
		// Confirm got move cursor
		yaw = l_yaw * -MOUSE_SENSITIVITY;
		TurnLeftAndRight(yaw);

		// Angle Calculation
		turningAngle += yaw;

		if (turningAngle < 0.0000f)
		{
			turningAngle += 360.f;
		}

		if (turningAngle > 360.0000f)
		{
			turningAngle -= 360.f;
		}
	}

	//For looking up limit
	if (l_pitch > 0.000f)
	{
		pitch = l_pitch * MOUSE_SENSITIVITY;

		float oldAngle = tiltingAngle;
		tiltingAngle += pitch;

		//if reach limits
		if (tiltingAngle > PITCH_LIMIT)
		{
			LookUpAndDown(PITCH_LIMIT - oldAngle);
			tiltingAngle = PITCH_LIMIT;
		}

		else
		{
			LookUpAndDown(pitch);
		}
	}

	//For looking down limit
	if (l_pitch < 0.000f)
	{
		pitch = l_pitch * MOUSE_SENSITIVITY;

		float oldAngle = tiltingAngle;
		tiltingAngle += pitch;

		//if reach limits
		if (tiltingAngle < -PITCH_LIMIT)
		{
			LookUpAndDown(-PITCH_LIMIT - oldAngle);
			tiltingAngle = -PITCH_LIMIT;
		}

		else
		{
			LookUpAndDown(pitch);
		}
	}
}

void Camera::LookUpAndDown(float a)
{
	Vector3 right = up.Cross(forward);
	right.y = 0;
	right.Normalize();

	q = Quaternion(a, right);
	forward = q * forward;
}

void Camera::TurnLeftAndRight(float a)
{
	q = Quaternion(a, up);
	forward = q * forward;
}

