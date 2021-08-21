#include "Vector4.h"


using namespace Utility;

Vector4::Vector4()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(0.0f)
{}

Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{}

Vector4 Vector4::operator+(const Vector4& vector) const {
	return Vector4(
		this->x + vector.x,
		this->y + vector.y,
		this->z + vector.z,
		this->w + vector.w
	);
}

Vector4 Vector4::operator+(float value) const {
	return Vector4(
		this->x + value,
		this->y + value,
		this->z + value,
		this->w + value
	);
}

Vector4 Vector4::operator-(const Vector4& vector) const {
	return Vector4(
		this->x - vector.x,
		this->y - vector.y,
		this->z - vector.z,
		this->w - vector.w
	);
}

Vector4 Vector4::operator-(float value) const {
	return Vector4(
		this->x - value,
		this->y - value,
		this->z - value,
		this->w - value
	);
}

Vector4 Vector4::operator*(const Vector4& vector) const {
	return Vector4(
		this->x * vector.x,
		this->y * vector.y,
		this->z * vector.z,
		this->w * vector.w
	);
}
Vector4 Vector4::operator*(float value) const {
	return Vector4(
		this->x * value,
		this->y * value,
		this->z * value,
		this->z * value
	);
}

Vector4 Vector4::operator/(const Vector4& vector) const {
	return Vector4(
		this->x / vector.x,
		this->y / vector.y,
		this->z / vector.z,
		this->w / vector.w
	);
}

Vector4 Vector4::operator/(float value) const {
	return Vector4(
		this->x / value,
		this->y / value,
		this->z / value,
		this->w / value
	);
}

Vector4 Vector4::operator- () const {
	return Vector4(-x, -y, -z, -w);
}

bool Vector4::operator ==(const Vector4& vector) const {
	if (abs(x - vector.x) <= 1e-5
		&& abs(y - vector.y) <= 1e-5
		&& abs(z - vector.z) <= 1e-5) 
	{
		return true;
	}

	return false;
}

float Vector4::dot(const Vector4& u, const Vector4& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}


