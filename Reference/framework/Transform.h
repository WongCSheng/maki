#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

#include "Matrix4f.h"
#include "MatrixStack.h"
#include "Vector3.h"
#include "Quaternion.h"

#include <vector>

using std::vector;

#define DEFAULTFORWARD Vector3(0, 0, 1)

// Transform Component
class Transform : public Component
{
	friend class Entity;
	friend class TransformSystem;
public:
	Transform();
	virtual ~Transform();

	const Matrix4f& TransformMat(void);
	void Set(Vector3 position = Vector3(0, 0, 0), Vector3 scale = Vector3(1, 1, 1), Quaternion rotation = Quaternion());
	void SetPosition(Vector3 position);
	void SetScale(Vector3 scale);
	void SetRotation(Quaternion rotation);
	void SetForward(Vector3 forward);

	void Translate(Vector3 translate);
	void Rotate(Quaternion rotate);
	// Scale By ( Uniform Scaling )
	void Scale(float scale);

	// Returns a reference to the transform's forward that cannot be modified
	const Vector3& Forward();

	Vector3 localposition;
	Quaternion localrotation;
	Vector3 localscale;
	Vector3 worldposition;
	Quaternion worldrotation;
	Vector3 worldscale;

private:
	Matrix4f Top;
	Vector3 forward;

	Matrix4f T, R, S;

	Transform* parent;
	vector<Transform*> children;
};

#endif