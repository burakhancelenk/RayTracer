#include "Plane.h"

#define PI 3.14159265

using namespace Primitive;

Plane::Plane()
	: m_center(0, 0, 0)
	, m_normal(0, 0, 1)
	, m_upVector(-1, 0, 0)
	, m_width(2)
	, m_height(2)
	, m_material()
{}

Plane::Plane(
	const Vector3& center,
	const Vector3& normal,
	const Vector3& upVector,
	float width,
	float height,
	bool isBackFaceCulling
)
	: m_center(center)
	, m_normal(normal.unit_vector())
	, m_upVector(upVector.unit_vector())
	, m_width(width)
	, m_height(height)
	, m_isBackFaceCulling(isBackFaceCulling)
	, m_material()
{
	m_sideVector = Vector3::cross(m_upVector, m_normal).unit_vector();
}

Plane::Plane(
	const Vector3& center,
	const Vector3& normal,
	const Vector3& upVector,
	float width,
	float height,
	bool isBackFaceCulling,
	const Material& material
)

	: m_center(center)
	, m_normal(normal.unit_vector())
	, m_upVector(upVector.unit_vector())
	, m_width(width)
	, m_height(height)
	, m_isBackFaceCulling(isBackFaceCulling)
	, m_material(material)
{
	m_sideVector = Vector3::cross(m_upVector, m_normal).unit_vector();
}

bool Plane::intersect_first_image(const Ray& ray) const
{
	float s = Vector3::dot(ray.direction, m_normal);

	if (!m_isBackFaceCulling) {
		if (acos(s) * 180.0 / PI < 90.0) {
			// Backface looking towards camera
			return false;
		}
	}

	if (s < 1e-6 && s >= -1e-6) {
		// Perpendicular to each other
		return false;
	}

	// Find the ratio of the projections onto normal vector
	float x = Vector3::dot((m_center - ray.origin), m_normal) / s;

	// Solve the ray's equation with the given ratio to find the hit point
	Vector3 hitPoint = ray.at(x);
	Vector3 localHitPoint = hitPoint - m_center;

	if (abs(Vector3::dot(m_upVector, localHitPoint)) <= m_height/2.0f
		&& abs(Vector3::dot(m_sideVector, localHitPoint)) <= m_width/2.0f)
	{
		// The hit point is on the plane
		return true;
	}

	// No instersection with the plane
	return false;
}

Hit Plane::intersect(const Ray& ray) const
{
	float s = Vector3::dot(ray.direction , m_normal);

	if (!m_isBackFaceCulling) {
		if ( acos(s)*180.0/PI < 90.0) {
			// Backface looking towards camera
			return Hit();
		}
	}

	if (s < 1e-8 && s >= -1e-8) {
		// Perpendicular to each other
		return Hit();
	}

	// Find the ratio of the projections onto normal vector
	float x = Vector3::dot((m_center - ray.origin) , m_normal) / s;

	// Solve the ray's equation with the given ratio to find the hit point
	Vector3 hitPoint = ray.at(x);
	Vector3 localHitPoint = hitPoint - m_center;

	if (abs(Vector3::dot(m_upVector, localHitPoint)) <= m_height/2.0f
		&& abs(Vector3::dot(m_sideVector, localHitPoint)) <= m_width/2.0f)
	{
		// The hit point is on the plane
		// Return hit informations
		return Hit{
		x >= 0,
		hitPoint,
		m_normal,
		m_material,
		(hitPoint - ray.origin).length()
		};
	}

	// No intersection with the plane
	return Hit();
}