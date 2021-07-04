#include "Plane.h"

using namespace Primitive;

Plane::Plane()
	: m_center(0,0,0)
	, m_normal(1,1,1)
	, m_material()
{}

Plane::Plane(const Vector3& center, const Vector3& normal)
	: m_center(center)
	, m_normal(normal)
	, m_material()
{}

Plane::Plane(
	const Vector3& center,
	const Vector3& normal,
	const Material& material)

	: m_center(center)
	, m_normal(normal)
	, m_material(material)
{}

bool Plane::intersect_first_image(const Ray& ray) const
{
	float s = Vector3::dot(ray.direction, m_normal);
	if (s < 1e-6 && s >= -1e-6) {
		// Perpendicular to each other
		return false;
	}
	return true;
}

Hit Plane::intersect(const Ray& ray) const
{
	float s = Vector3::dot(ray.direction , m_normal);
	if (s < 1e-6 && s >= -1e-6) {
		// Perpendicular to each other
		return Hit();
	}

	// Find the ratio of the projections onto normal vector
	float x = Vector3::dot((m_center - ray.origin) , m_normal) / s;

	// Solve the ray's equation with the given ratio to find the hit point
	Vector3 hitPoint = ray.at(x);

	// Return hit informations
	return Hit{
		x >= 0,
		hitPoint,
		m_normal,
		m_material,
		x
	};
}