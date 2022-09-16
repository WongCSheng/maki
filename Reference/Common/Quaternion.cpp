#include "Quaternion.h"

Quaternion::Quaternion(void)
{
	w = 1;
}

Quaternion::Quaternion(float a, const Vector3& n) throw(DivideByZero)
{
	a = Math::DegreeToRadian(a);

	// rmb .. if w == 1, no rotation at all .. because user input a == 0 .. cos (0) is always 1;
	w = cos(a / 2);

	if (Math::FAbs(w) < Math::EPSILON)
		w = 0;

	v = n*sin(a / 2);
}

const Quaternion Quaternion::Inverted() const
{
	Quaternion q;
	q.w = w;
	q.v = -v;

	return q;
}


const Quaternion Quaternion::operator*(const Quaternion& q) const
{
	// Multiplying two quaternions together combines the rotation

	Quaternion r;

	r.w = w*q.w - v.Dot(q.v);
	r.v = v*q.w + q.v*w + v.Cross(q.v);

	return r;
}

// Rotate a vector with this quaternion.
// The basic equation is qpq* (the * means inverse) but we use a simplified version of that equation. for right hand rule .. is q*pq
const Vector3 Quaternion::operator*(const Vector3& V) const
{
	//   Quaternion p;
	//p.w = 0;
	//p.v = V;
	//// Could do it this way:
	//
	//const Quaternion& q = (*this);
	//   return (q.Inverted() * p * q).v;


	// But let's optimize it a bit instead.
	Vector3 vcV = v.Cross(V);
	Vector3 returnVec = V + vcV*(2 * w) + v.Cross(vcV) * 2;

	// check for error
	if (Math::FAbs(returnVec.x) < Math::EPSILON)
		returnVec.x = 0.f;

	if (Math::FAbs(returnVec.y) < Math::EPSILON)
		returnVec.y = 0.f;

	if (Math::FAbs(returnVec.z) < Math::EPSILON)
		returnVec.z = 0.f;

	return returnVec;
}

float Quaternion::length(void) const
{
	return sqrt(v.LengthSquared() + (w * w));
}

Quaternion Quaternion::normalized(void) const throw(DivideByZero)
{
	float d = length();
	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		throw DivideByZero();

	Quaternion tq;

	tq.w = this->w / d;
	tq.v.x = this->v.x / d;
	tq.v.y = this->v.y / d;
	tq.v.z = this->v.z / d;

	return tq;
}

Quaternion& Quaternion::Normalize(void) throw(DivideByZero)
{
	float d = length();
	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		throw DivideByZero();
	w /= d;
	v.x /= d;
	v.y /= d;
	v.z /= d;
	return *this;
}

Matrix4f Quaternion::convertTomat4(void)
{
	Quaternion nq = this->Normalize();

	float qw = nq.w;
	float qx = nq.v.x;
	float qy = nq.v.y;
	float qz = nq.v.z;

	float n = qw * qw + qx * qx + qy * qy + qz * qz;

	Matrix4f qMtx;
	qMtx.a[0] = 1.0f - (2.0f*qy*qy) - (2.0f*qz*qz);
	qMtx.a[1] = (2.0f*qx*qy) - (2.0f*qz*qw);
	qMtx.a[2] = (2.0f*qx*qz) + (2.0f*qy*qw);
	qMtx.a[3] = 0.0f;

	qMtx.a[4] = (2.0f*qx*qy) + (2.0f*qz*qw);
	qMtx.a[5] = 1.0f - (2.0f*qx*qx) - (2.0f*qz*qz);
	qMtx.a[6] = (2.0f*qy*qz) - (2.0f*qx*qw);
	qMtx.a[7] = 0.0f;

	qMtx.a[8] = (2.0f*qx*qz) - (2.0f*qy*qw);
	qMtx.a[9] = (2.0f*qy*qz) + (2.0f*qx*qw);
	qMtx.a[10] = 1.0f - (2.0f*qx*qx) - (2.0f*qy*qy);
	qMtx.a[11] = 0.0f;

	qMtx.a[12] = 0.0f;
	qMtx.a[13] = 0.0f;
	qMtx.a[14] = 0.0f;
	qMtx.a[15] = 1.0f;

	// error check
	for (unsigned int i = 0; i < 16; i++)
	{
		if (Math::FAbs(qMtx.a[i]) < Math::EPSILON)
			qMtx.a[i] = 0;
	}

	qMtx.Transpose();       // change to right-hand rule for opengl

	return qMtx;
}

void Quaternion::ToAxisAngle(Vector3& vecAxis, float& flAngle) const
{
	// Convert the quaternion back into axis/angle
	if (v.LengthSquared() < 0.0001f)
		vecAxis = Vector3(1, 0, 0);
	else
		vecAxis = v.Normalized();

	// This is the opposite procedure as explained in
	// w = cos(a/2) and a = acos(w)*2
	flAngle = acos(w) * 2;

	// Convert to degrees
	flAngle = Math::RadianToDegree(flAngle);
}


const Quaternion Quaternion::Slerp(const Quaternion& other, float t) const
{
	const Quaternion& q = *this;
	Quaternion r = other;

	// This is the quaternion equation that I discuss in the video, and it works just fine!
	// return ((r * q.Inverted()) ^ t) * q;

	// But this one is faster. For the derivation, see "3D Primer For Graphics
	// and Game Development" by Dunn and Parberry, section 10.4.13. I may go
	// over this one in a future video, but the two formulas come out the same.
	// (Hint: I'm more likely to do it if I get a request!)
	float flCosOmega = w*r.w + r.v.Dot(v);
	if (flCosOmega < 0)
	{
		// Avoid going the long way around.
		r.w = -r.w;
		r.v = -r.v;
		flCosOmega = -flCosOmega;
	}

	float k0, k1;
	if (flCosOmega > 0.9999f)
	{
		// Very close, use a linear interpolation.
		k0 = 1 - t;
		k1 = t;
	}
	else
	{
		// Trig identity, sin^2 + cos^2 = 1
		float flSinOmega = sqrt(1 - flCosOmega*flCosOmega);

		// Compute the angle omega
		float flOmega = atan2(flSinOmega, flCosOmega);
		float flOneOverSinOmega = 1 / flSinOmega;

		k0 = sin((1 - t)*flOmega) * flOneOverSinOmega;
		k1 = sin(t*flOmega) * flOneOverSinOmega;
	}

	// Interpolate
	Quaternion result;
	result.w = q.w * k0 + r.w * k1;
	result.v = q.v * k0 + r.v * k1;

	return result;
}

Quaternion::~Quaternion(void)
{
}