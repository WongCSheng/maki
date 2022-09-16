#include "Matrix4f.h"

Matrix4f::Matrix4f(float a00, float a10, float a20, float a30, float a01, float a11, float a21, float a31, float a02, float a12, float a22, float a32, float a03, float a13, float a23, float a33) {
	a[0] = a00;
	a[1] = a10;
	a[2] = a20;
	a[3] = a30;
	a[4] = a01;
	a[5] = a11;
	a[6] = a21;
	a[7] = a31;
	a[8] = a02;
	a[9] = a12;
	a[10] = a22;
	a[11] = a32;
	a[12] = a03;
	a[13] = a13;
	a[14] = a23;
	a[15] = a33;
}

Matrix4f::Matrix4f(const float m[16]) {
	for(int i = 0; i < 16; i++)
		a[i] = m[i];
}

Matrix4f::Matrix4f(const Matrix4f &rhs) {
	for(int i = 0; i < 16; i++)
		a[i] = rhs.a[i];
}

void Matrix4f::SetToIdentity(void) {
	SetToZero();
	a[0] = a[5] = a[10] = a[15] = 1;
}

void swap(float &v1, float &v2) {
	float temp = v1;
	v1 = v2;
	v2 = temp;
}

void Matrix4f::Transpose(void) {
	for(int i = 0; i < 4; i++)
		for(int j = i + 1; j < 4; j++)
			swap(a[i * 4 + j], a[j * 4 + i]);
}

void Matrix4f::SetToZero(void) {
	for(int i = 0; i < 16; i++)
		a[i] = 0;
}

Matrix4f Matrix4f::GetTranspose() const {
	Matrix4f ret(*this);
	ret.Transpose();
	return ret;
}

Matrix4f Matrix4f::GetInverse() const throw( DivideByZero ) {
	float a0 = a[ 0]*a[ 5] - a[ 1]*a[ 4];
    float a1 = a[ 0]*a[ 6] - a[ 2]*a[ 4];
    float a2 = a[ 0]*a[ 7] - a[ 3]*a[ 4];
    float a3 = a[ 1]*a[ 6] - a[ 2]*a[ 5];
    float a4 = a[ 1]*a[ 7] - a[ 3]*a[ 5];
    float a5 = a[ 2]*a[ 7] - a[ 3]*a[ 6];
    float b0 = a[ 8]*a[13] - a[ 9]*a[12];
    float b1 = a[ 8]*a[14] - a[10]*a[12];
    float b2 = a[ 8]*a[15] - a[11]*a[12];
    float b3 = a[ 9]*a[14] - a[10]*a[13];
    float b4 = a[ 9]*a[15] - a[11]*a[13];
    float b5 = a[10]*a[15] - a[11]*a[14];

    float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	if(abs(det) < Math::EPSILON)
		throw DivideByZero();
    Matrix4f inverse;
	if (Math::FAbs(det) > Math::EPSILON)
    {
        inverse.a[ 0] = + a[ 5]*b5 - a[ 6]*b4 + a[ 7]*b3;
        inverse.a[ 4] = - a[ 4]*b5 + a[ 6]*b2 - a[ 7]*b1;
        inverse.a[ 8] = + a[ 4]*b4 - a[ 5]*b2 + a[ 7]*b0;
        inverse.a[12] = - a[ 4]*b3 + a[ 5]*b1 - a[ 6]*b0;
        inverse.a[ 1] = - a[ 1]*b5 + a[ 2]*b4 - a[ 3]*b3;
        inverse.a[ 5] = + a[ 0]*b5 - a[ 2]*b2 + a[ 3]*b1;
        inverse.a[ 9] = - a[ 0]*b4 + a[ 1]*b2 - a[ 3]*b0;
        inverse.a[13] = + a[ 0]*b3 - a[ 1]*b1 + a[ 2]*b0;
        inverse.a[ 2] = + a[13]*a5 - a[14]*a4 + a[15]*a3;
        inverse.a[ 6] = - a[12]*a5 + a[14]*a2 - a[15]*a1;
        inverse.a[10] = + a[12]*a4 - a[13]*a2 + a[15]*a0;
        inverse.a[14] = - a[12]*a3 + a[13]*a1 - a[14]*a0;
        inverse.a[ 3] = - a[ 9]*a5 + a[10]*a4 - a[11]*a3;
        inverse.a[ 7] = + a[ 8]*a5 - a[10]*a2 + a[11]*a1;
        inverse.a[11] = - a[ 8]*a4 + a[ 9]*a2 - a[11]*a0;
        inverse.a[15] = + a[ 8]*a3 - a[ 9]*a1 + a[10]*a0;

        float invDet = ((float)1)/det;
        inverse.a[ 0] *= invDet;
        inverse.a[ 1] *= invDet;
        inverse.a[ 2] *= invDet;
        inverse.a[ 3] *= invDet;
        inverse.a[ 4] *= invDet;
        inverse.a[ 5] *= invDet;
        inverse.a[ 6] *= invDet;
        inverse.a[ 7] *= invDet;
        inverse.a[ 8] *= invDet;
        inverse.a[ 9] *= invDet;
        inverse.a[10] *= invDet;
        inverse.a[11] *= invDet;
        inverse.a[12] *= invDet;
        inverse.a[13] *= invDet;
        inverse.a[14] *= invDet;
        inverse.a[15] *= invDet;
    }
	return inverse;
}

Matrix4f Matrix4f::operator*(const Matrix4f& rhs) const {
	Matrix4f ret;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			ret.a[i * 4 + j] = a[0 * 4 + j] * rhs.a[i * 4 + 0] + a[1 * 4 + j] * rhs.a[i * 4 + 1] + a[2 * 4 + j] * rhs.a[i * 4 + 2] + a[3 * 4 + j] * rhs.a[i * 4 + 3];
	return ret;
}

Matrix4f Matrix4f::operator+(const Matrix4f& rhs) const {
	return Matrix4f(
		a[0] + rhs.a[0],
		a[1] + rhs.a[1],
		a[2] + rhs.a[2],
		a[3] + rhs.a[3],
		a[4] + rhs.a[4],
		a[5] + rhs.a[5],
		a[6] + rhs.a[6],
		a[7] + rhs.a[7],
		a[8] + rhs.a[8],
		a[9] + rhs.a[9],
		a[10] + rhs.a[10],
		a[11] + rhs.a[11],
		a[12] + rhs.a[12],
		a[13] + rhs.a[13],
		a[14] + rhs.a[14],
		a[15] + rhs.a[15]
		);
}

Matrix4f& Matrix4f::operator=(const Matrix4f& rhs) {
	for(int i = 0; i < 16; i++)
		a[i] = rhs.a[i];
	return *this;
}

Matrix4f Matrix4f::operator*(float scalar) const {
	Matrix4f ret;
	for(int i = 0; i < 16; i++)
		ret.a[i] = scalar * a[i];
	return ret;
}

Vector3 Matrix4f::operator*(const Vector3& rhs) const {
	float b[4];
	for(int i = 0; i < 4; i++)
		b[i] = (a[0 * 4 + i] * rhs.x) + (a[1 * 4 + i] * rhs.y) + (a[2 * 4 + i] * rhs.z) + (a[3 * 4 + i] * 1);
	Vector3 ret(b[0], b[1], b[2]);
	return ret;
}

void Matrix4f::SetToRotation(float degrees, float axisX, float axisY, float axisZ) throw( DivideByZero ) {
	double mag = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
	if(Math::FAbs((float)mag) < Math::EPSILON)
		throw DivideByZero();
	double x = axisX / mag, y = axisY / mag, z = axisZ/ mag;
	double c = cos(degrees * Math::PI / 180), s = sin(degrees * Math::PI / 180);
	a[0] = (float)(x * x * (1.f - c) + c);
	a[1] = (float)(y * x * (1.f - c) + z * s);
	a[2] = (float)(x * z * (1.f - c) - y * s);
	a[3] = 0;
	a[4] = (float)(x * y * (1.f - c) - z * s);
	a[5] = (float)(y * y * (1.f - c) + c);
	a[6] = (float)(y * z * (1.f - c) + x * s);
	a[7] = 0;
	a[8] = (float)(x * z * (1.f - c) + y * s);
	a[9] = (float)(y * z * (1.f - c) - x * s);
	a[10] = (float)(z * z * (1.f - c) + c);
	a[11] = 0;
	a[12] = 0;
	a[13] = 0;
	a[14] = 0;
	a[15] = 1;
}

void Matrix4f::SetToScale(float sx, float sy, float sz) {
	SetToIdentity();
	a[0] = sx;
	a[5] = sy;
	a[10] = sz;
}

void Matrix4f::SetToTranslation(float tx, float ty, float tz) {
	SetToIdentity();
	a[12] = tx;
	a[13] = ty;
	a[14] = tz;
}

void Matrix4f::SetToFrustum(double left, double right, double bottom, double top, double near, double far) {
	*this = Matrix4f((float)(2 * near / (right - left)), 0, 0, 0,
		0, (float)(2 * near / (top - bottom)), 0, 0,
		(float)((right + left) / (right - left)), (float)((top + bottom) / (top - bottom)), - (float)((far + near) / (far - near)), -1,
		0, 0, - (float)(2 * far * near / (far - near)), 0);
}

void Matrix4f::SetToLookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ) 
{
	Vector3 eye((float)(eyeX), (float)(eyeY), (float)(eyeZ));
	Vector3 target((float)(centerX), (float)(centerY), (float)(centerZ));
	Vector3 up((float)(upX), (float)(upY), (float)(upZ));

	Vector3 zaxis = (eye - target).Normalized();    // The "forward" vector.
	Vector3 xaxis = (up.Cross(zaxis)).Normalized();// The "right" vector.
	Vector3 yaxis = zaxis.Cross(xaxis);     // The "up" vector.

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	Matrix4f viewMatrix(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye), 1);

	*this = viewMatrix;
}

void Matrix4f::SetToPerspective(double fovy, double aspect, double zNear, double zFar) {
	double f = 1.0 / tan(Math::PI / 180 * fovy / 2);
	*this = Matrix4f((float)(f / aspect), 0, 0, 0,
		0, (float)f, 0, 0,
		0, 0, (float)((zFar + zNear) / (zNear - zFar)), -1,
		0, 0, (float)(2 * zFar * zNear / (zNear - zFar)), 0);
}

void Matrix4f::SetToOrtho(double left, double right, double bottom, double top, double nearVal, double farVal) {
	*this = Matrix4f(2 / (float)(right - left), 0, 0, 0,
		0, 2 / (float)(top - bottom), 0, 0,
		0, 0, - 2 / (float)(farVal - nearVal), 0,
		- (float)((right + left) / (right - left)), - (float)((top + bottom) / (top - bottom)), - (float)((farVal + nearVal) / (farVal - nearVal)), 1);
}
