#include "Sphere.h"

using namespace Primitive;

Sphere::Sphere() 
	: m_center(0,0,0)
	, m_radius(1)
	, m_material()
{}

Sphere::Sphere(const Vector3& center, float radius) 
	: m_center(center)
	, m_radius(radius)
	, m_material()
{}

Sphere::Sphere(
	const Vector3& center,
	float radius,
	const Material& material)

	: m_center(center)
	, m_radius(radius)
	, m_material(material)
{}

bool Sphere::intersect_first_image(const Ray& ray) const
{
	Vector3 oc = m_center - ray.origin;
	float ohd = Vector3::dot(oc,ray.direction);
	if (ohd < 0) {
		// If the sphere is "behind" the origin, there's no hit
		return false;
	}
	Vector3 oh = ray.direction * ohd;
	float d = (oc - oh).length();
	return d <= m_radius;
}

Hit Sphere::intersect(const Ray& ray) const
{
	Vector3 oc = m_center - ray.origin;

	// First we solve a quadratic equation
	float da = 1;
	float db = -2 * Vector3::dot(oc , ray.direction);
	float dc = Vector3::dot(oc , oc) - m_radius * m_radius;
	float det = db * db - 4 * da * dc;
	if (det < 0) return Hit();
	float sqrtDet = std::sqrtf(det);
	float s = 1 / (2 * da);
	float x1 = (-db + sqrtDet) * s;
	float x2 = (-db - sqrtDet) * s;

	// x1 and x2 are the two (maybe equal) roots
	// There is a hit if and only if x >= 0 (the ray must not go backward, so the
	// the hit point cannot be "behind" the origin) and we care about the first
	// hit, in other words smaller smaller root.
	float x = 0;
	if (x1 < 0) {
		if (x2 < 0) return Hit();
		x = x2;
	}
	else
	{
		if (x2 < 0) x = x1;
		else x = std::min(x1, x2);
	}

	// Solve the ray's equation with the given root to find the hit point
	Vector3 hitPoint = ray.at(x);

	// Return hit informations
	return Hit {
		true,
		hitPoint,
		(hitPoint - m_center).unit_vector(),
		m_material,
		x
	};
}
