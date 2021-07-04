#include "Vector3.h"

using namespace Utility;

Vector3::Vector3()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{}

Vector3::Vector3(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
{}

Vector3 Vector3::operator+(const Vector3& vector) const {
	return Vector3(
		this->x + vector.x,
		this->y + vector.y,
		this->z + vector.z
	);
}

Vector3 Vector3::operator+(float value) const {
	return Vector3(
		this->x + value,
		this->y + value,
		this->z + value
	);
}

Vector3 Vector3::operator-(const Vector3& vector) const {
	return Vector3(
		this->x - vector.x,
		this->y - vector.y,
		this->z - vector.z
	);
}

Vector3 Vector3::operator-(float value) const {
	return Vector3(
		this->x - value,
		this->y - value,
		this->z - value
	);
}

Vector3 Vector3::operator*(const Vector3& vector) const {
	return Vector3(
		this->x * vector.x,
		this->y * vector.y,
		this->z * vector.z
	);
}
Vector3 Vector3::operator*(float value) const {
	return Vector3(
		this->x * value,
		this->y * value,
		this->z * value
	);
}

Vector3 Vector3::operator/(const Vector3& vector) const {
	return Vector3(
		this->x / vector.x,
		this->y / vector.y,
		this->z / vector.z
	);
}

Vector3 Vector3::operator/(float value) const {
	return Vector3(
		this->x / value,
		this->y / value,
		this->z / value
	);
}

Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3& vector) const {
	if (abs(x - vector.x) <= 1e-5
		&& y == vector.y <= 1e-5
		&& abs(z == vector.z) <= 1e-5)
	{
		return true;
	}

	return false;
}


Vector3 Vector3::reflect(const Vector3& vector) const
{
	return *this*(dot(*this,vector)*2) - vector;
}


float Vector3::dot(const Vector3& u, const Vector3& v){
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector3 Vector3::cross(const Vector3& u, const Vector3& v){
	return Vector3(
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	);
}

float Vector3::length() const {
	return sqrt(length_squared());
}

float Vector3::length_squared() const {
	return x * x + y * y + z * z;
}

Vector3 Vector3::unit_vector() const{
	return Vector3(x,y,z) / length();
}

