#include "MatrixStack.h"

/******************************************************************************/
/*!
\brief
MS default constructor
*/
/******************************************************************************/
MS::MS() {
	Matrix4f mat;
	mat.SetToIdentity();
	ms.push(mat);
}

/******************************************************************************/
/*!
\brief
MS destructor
*/
/******************************************************************************/
MS::~MS() {
}

/******************************************************************************/
/*!
\brief
Return the top matrix on the matrix stack

\return
	A copy of the top matrix
*/
/******************************************************************************/
const Matrix4f& MS::Top() const {
	return ms.top();
}

/******************************************************************************/
/*!
\brief
Pop the top matrix on the matrix stack
*/
/******************************************************************************/
void MS::PopMatrix() {
	ms.pop();
}

/******************************************************************************/
/*!
\brief
Make a copy of the top matrix on the matrix stack and push it on top
*/
/******************************************************************************/
void MS::PushMatrix() {
	ms.push(ms.top());
}

/******************************************************************************/
/*!
\brief
Clear the matrix stack
*/
/******************************************************************************/
void MS::Clear() {
	while(ms.size() > 1)
		ms.pop();
}

/******************************************************************************/
/*!
\brief
Replace the top matrix with an identity matrix
*/
/******************************************************************************/
void MS::LoadIdentity() {
	Matrix4f mat;
	mat.SetToIdentity();
	ms.top() = mat;
}

/******************************************************************************/
/*!
\brief
Return the top matrix with a new matrix

\param matrix
	The new matrix to replace the top
*/
/******************************************************************************/
void MS::LoadMatrix(const Matrix4f &matrix) {
	ms.top() = matrix;
}

/******************************************************************************/
/*!
\brief
Multiply the top matrix with a new matrix

\param matrix
	The new matrix to replace the top
*/
/******************************************************************************/
void MS::MultMatrix(const Matrix4f &matrix) {
	ms.top() = ms.top() * matrix;
}

/******************************************************************************/
/*!
\brief
Multiply the top matrix with a rotation matrix based on the following parameters

\param	degrees
	Angle of rotation, in degrees, clockwise
\param	axisX
	X-component of the rotation axis
\param	axisY
	Y-component of the rotation axis
\param	axisZ
	Z-component of the rotation axis
*/
/******************************************************************************/
void MS::Rotate(float degrees, float axisX, float axisY, float axisZ) {
	Matrix4f mat;
	mat.SetToRotation(degrees, axisX, axisY, axisZ);
	ms.top() = ms.top() * mat;
}

void MS::QuaternionRotate(float w, Vector3 v)
{
		Matrix4f mat;
		Quaternion q = Quaternion(w, v);
		mat = q.convertTomat4();
		ms.top() = ms.top() * mat;
}

void MS::QuaternionRotate(Quaternion q)
{
	Matrix4f mat;
	mat = q.convertTomat4();
	ms.top() = ms.top() * mat;
}

/******************************************************************************/
/*!
\brief
Multiply the top matrix with a scale matrix based on the following parameters

\param	scaleX
	Factor to scale along x-axis
\param	scaleY
	Factor to scale along y-axis
\param	scaleZ
	Factor to scale along z-axis
*/
/******************************************************************************/
void MS::Scale(float scaleX, float scaleY, float scaleZ) {
	Matrix4f mat;
	mat.SetToScale(scaleX, scaleY, scaleZ);
	ms.top() = ms.top() * mat;
}

/******************************************************************************/
/*!
\brief
Multiply the top matrix with a translation matrix based on the following 
parameters

\param	translateX
	Offset along x-axis
\param	scaleY
	Offset along y-axis
\param	scaleZ
	Offset along z-axis
*/
/******************************************************************************/
void MS::Translate(float translateX, float translateY, float translateZ) {
	Matrix4f mat;
	mat.SetToTranslation(translateX, translateY, translateZ);
	ms.top() = ms.top() * mat;
}

/******************************************************************************/
/*!
\brief
Setup frustum matrix and push to matrix stack

\param left
	Frustum - left 
\param right
	Frustum - right 
\param bottom
	Frustum - bottom 
\param top
	Frustum - top 
\param near
	Frustum - front
\param far
	Frustum - back
*/
/******************************************************************************/
void MS::Frustum(double left, double right, double bottom, double top, double near, double far) {
	Matrix4f mat;
	mat.SetToFrustum(left, right, bottom, top, near, far);
	ms.top() = ms.top() * mat;
}

/******************************************************************************/
/*!
\brief Setup lookat matrix and push to matrix stack

\param eyeX
	eye vector x value
\param eyeY
	eye vector y value
\param eyeZ
	eye vector z value
\param centerX
	target position x value
\param centerY
	target position y value
\param centerZ
	target position z value
\param upX
	up vector x value
\param upY
	up vector y value
\param upZ
	up vector z value
*/
/******************************************************************************/
void MS::LookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ)
{
	Matrix4f mat;
	mat.SetToLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	ms.top() = ms.top() * mat;
}
