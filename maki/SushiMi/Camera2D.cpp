#include "Camera2D.h"
#include "include/Vector.h"
#include <glm/glm/trigonometric.hpp>

/*global variables*/
GLboolean first_person_cam = GL_FALSE;

void Camera2D::init(GLFWwindow* pWindow, Object* ptr)
{
	// assign address of object of type GLApp::GLObject with name "Camera" in objects
	pgo = &Object::objects.at("Camera");

	// compute camera window's aspect ratio
	GLsizei fb_width, fb_height;
	glfwGetFramebufferSize(pWindow, &fb_width, &fb_height);
	ar = static_cast<GLfloat>(fb_width) / static_cast<GLfloat>(fb_height);

	// compute camera's up and right vectors
	up = { -sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)), cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)) };
	right = { cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)), sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)) };

	// at startup, camera must be initialized to free camera
	view_xform.a[1] = view_xform.a[2] = view_xform.a[3] = view_xform.a[5] = 0;
	view_xform.a[0] = view_xform.a[4] = view_xform.a[8] = 1;
	view_xform.a[6] = -pgo->position.x;
	view_xform.a[1] = -pgo->position.y;

	GLfloat cam_W = ar * GLHelper::height;
	GLfloat cam_H = ar * GLHelper::width;
	// compute other matrices

	camwin_to_ndc_xform.a[1] = camwin_to_ndc_xform.a[2] = camwin_to_ndc_xform.a[3] = camwin_to_ndc_xform.a[5] = camwin_to_ndc_xform.a[6] = camwin_to_ndc_xform.a[7] = 0;
	camwin_to_ndc_xform.a[0] = 2 / cam_W;
	camwin_to_ndc_xform.a[4] = 2 / cam_H;
	camwin_to_ndc_xform.a[8] = 1;
	world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
}

void Camera2D::update(GLFWwindow* pWindow)
{
	ar = (GLfloat)GLHelper::width / (GLfloat)GLHelper::height;
	// update POV
	if (camtype_flag == GL_TRUE)
	{
		if (first_person_cam == GL_FALSE)
		{
			first_person_cam = GL_TRUE;
		}
		else if (first_person_cam == GL_TRUE)
		{
			first_person_cam = GL_FALSE;
		}
		camtype_flag = GL_FALSE;
	}

	if (first_person_cam == GL_TRUE)
	{
		gfxVector2 nrm_up, nrm_right;
		nrm_right.Normalize(nrm_right, right);
		nrm_up.Normalize(nrm_up, up);

		view_xform.a[0] = right.x;
		view_xform.a[1] = up.x;
		view_xform.a[2] = 0.f;
		view_xform.a[3] = right.y;
		view_xform.a[4] = up.y;
		view_xform.a[5] = 0.f;
		view_xform.a[6] = (-nrm_right * pgo->position);
		view_xform.a[7] = (nrm_up * pgo->position);
		view_xform.a[8] = 1.f;
	}
	else if (first_person_cam == GL_FALSE)
	{
		view_xform.a[1] = view_xform.a[2] = view_xform.a[3] = view_xform.a[5] = 0;
		view_xform.a[0] = view_xform.a[4] = view_xform.a[8] = 1;
		view_xform.a[6] = -pgo->position.x;
		view_xform.a[1] = -pgo->position.y;
	}
	if (left_turn_flag == GL_TRUE)
	{
		pgo->orientation.x += pgo->orientation.y;
	}
	if (right_turn_flag == GL_TRUE)
	{
		pgo->orientation.x -= pgo->orientation.y;
	}
	// update camera's up and right vectors (if required)

	up = { -sinf(glm::radians(pgo->orientation.x)),
			cosf(glm::radians(pgo->orientation.x)) };

	right = { cosf(glm::radians(pgo->orientation.x)),
				sinf(glm::radians(pgo->orientation.x)) };

	// update camera's position (if required) 
	if (move_flag == GL_TRUE)
	{
		gfxVector2 nrm_up;
		nrm_up.Normalize(nrm_up,up);
		pgo->position += (linear_speed * nrm_up);//displace the camera
	}

	// implement camera's zoom effect (if required)
	if (zoom_flag == GL_TRUE)
	{
		if (height <= min_height)
		{
			height_chg_dir = 1;
		}
		else if (height >= max_height)
		{
			height_chg_dir = -1;
		}
		height += (height_chg_dir * height_chg_val);
	}


	// compute window-to-NDC transformation matrix
	// compute other matrices ...

	camwin_to_ndc_xform.a[1] = camwin_to_ndc_xform.a[2] = camwin_to_ndc_xform.a[3] = camwin_to_ndc_xform.a[5] = camwin_to_ndc_xform.a[6] = camwin_to_ndc_xform.a[7] = 0;
	camwin_to_ndc_xform.a[0] = 2 / (height * ar);
	camwin_to_ndc_xform.a[4] = 2 / height;
	camwin_to_ndc_xform.a[8] = 1;

	GLfloat radians = glm::radians(camera2d.pgo->orientation.x);

	gfxMatrix3 scale_mat;
	scale_mat.a[0] = camera2d.pgo->scaling.x;
	scale_mat.a[1] = 0;
	scale_mat.a[2] = 0;
	scale_mat.a[3] = 0;
	scale_mat.a[4] = camera2d.pgo->scaling.y;
	scale_mat.a[5] = 0;
	scale_mat.a[6] = 0;
	scale_mat.a[7] = 0;
	scale_mat.a[8] = 1;

	gfxMatrix3 rot_mat;
	rot_mat.a[0] = cos(radians);
	rot_mat.a[1] = sin(radians);
	rot_mat.a[3] = -sin(radians);
	rot_mat.a[4] = cos(radians);
	rot_mat.a[2] = rot_mat.a[5] = rot_mat.a[6] = rot_mat.a[7] = rot_mat.a[8] = 0;

	gfxMatrix3 trans_mat;
	trans_mat.a[0] = 1;
	trans_mat.a[1] = 0;
	trans_mat.a[2] = 0;
	trans_mat.a[3] = 0;
	trans_mat.a[4] = 1;
	trans_mat.a[5] = 0;
	trans_mat.a[6] = camera2d.pgo->position.x;
	trans_mat.a[7] = camera2d.pgo->position.y;
	trans_mat.a[0] = 1;
	gfxMatrix3 model_mtx = trans_mat * rot_mat * scale_mat;
	camera2d.pgo->mdl_to_ndc_xform = world_to_ndc_xform * model_mtx;
	// compute world-to-NDC transformation matrix
	world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
}