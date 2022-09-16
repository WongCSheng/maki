#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <stack>
#include "Matrix4f.h"
#include "Quaternion.h"

class MS {
	std::stack<Matrix4f> ms;
public:
	MS();
	~MS();
	const Matrix4f& Top() const;
	void PopMatrix();
	void PushMatrix();
	void Clear();
	void LoadIdentity();
	void LoadMatrix(const Matrix4f &matrix);
	void MultMatrix(const Matrix4f &matrix);
	void Rotate(float degrees, float axisX, float axisY, float axisZ);
	void Scale(float scaleX, float scaleY, float scaleZ);
	void Translate(float translateX, float translateY, float translateZ);
	void Frustum(double left, double right, double	bottom, double top, double near, double far);
	void LookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ);
	void QuaternionRotate(float w, Vector3 v);
	void QuaternionRotate(Quaternion q);
};

#endif
