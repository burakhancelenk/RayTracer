#include "Cone.h"

#define PI 3.14159265

using namespace Primitive;

Cone::Cone()
	: m_center(0, 0, 0)
	, m_direction(0, 0, 1)
	, m_radius(0.5)
	, m_height(2)
	, m_material()
{
	// Prepare the top point, angle and bottom disk according to the given informations
	m_bottom = Disk(m_center,
		-m_direction,
		m_radius,
		false,
		m_material);

	m_topPoint = m_direction * m_height + m_center;
	m_angle = acos( Vector3::dot(m_direction, (m_direction * m_height 
					+ Vector3(-m_direction.z, 0, -m_direction.x).unit_vector() * m_radius).unit_vector()) );

}

Cone::Cone(
	const Vector3& center,
	const Vector3& direction,
	float radius,
	float height)

	: m_center(center)
	, m_direction(direction.unit_vector())
	, m_radius(radius)
	, m_height(height)
	, m_material()
{

	// Prepare the top point, angle and bottom disk according to the given informations
	m_bottom = Disk(m_center,
		-m_direction,
		m_radius,
		false,
		m_material);

	m_topPoint = m_direction * m_height + m_center;
	m_angle = acos(Vector3::dot(m_direction, (m_direction * m_height
		+ Vector3(-m_direction.z, 0, -m_direction.x).unit_vector() * m_radius).unit_vector()));
}

Cone::Cone(
	const Vector3& topPoint,
	float angle,
	const Vector3& direction,
	float height) 

	: m_topPoint(topPoint)
	, m_angle(angle)
	, m_direction(-direction)
	, m_height(height)
	, m_material()
{

	// Prepare the center, radius and bottom disk according to the given informations
	m_center = m_topPoint - m_direction * m_height;
	m_radius = m_height * sin(m_angle) / sin(PI - m_angle);

	m_bottom = Disk(m_center,
		-m_direction,
		m_radius,
		false,
		m_material);

}

Cone::Cone(
	const Vector3& center,
	const Vector3& direction,
	float radius,
	float height,
	const Material& material)

	: m_center(center)
	, m_direction(direction.unit_vector())
	, m_radius(radius)
	, m_height(height)
	, m_material(material)
{

	// Prepare the top point, angle and bottom disk according to the given informations
	m_bottom = Disk(m_center,
		-m_direction,
		m_radius,
		false,
		m_material);

	m_topPoint = m_direction * m_height + m_center;
	m_angle = acos(Vector3::dot(m_direction, (m_direction * m_height
		+ Vector3(-m_direction.z, 0, -m_direction.x).unit_vector() * m_radius).unit_vector()));

}

Cone::Cone(
	const Vector3& topPoint,
	float angle,
	const Vector3& direction,
	float height,
	const Material& material)

	: m_topPoint(topPoint)
	, m_direction(-direction)
	, m_angle(angle)
	, m_height(height)
	, m_material(material)
{

	// Prepare the center, radius and bottom disk according to the given informations
	m_center = m_topPoint - m_direction * m_height;
	m_radius = m_height * sin(m_angle) / sin(PI - m_angle);

	m_bottom = Disk(m_center,
		-m_direction,
		m_radius,
		false,
		m_material);

}

bool Cone::intersect_first_image(const Ray& ray) const
{
	/// Intersection check for bottom disk ///
	Hit bottomHit = m_bottom.intersect(ray);

	if (bottomHit.isValid) {
		return true;
	}

	/// Intersection check for body of the cone ///
	Vector3 D = -m_direction; // Direction from top point to the center of the bottom disk
	Vector3 V = m_topPoint;
	Vector3 R = ray.direction;
	Vector3 Ro = ray.origin;

	// Create a quadratic equation from the implicit equation of the cone and solve it.
	// The implicit equation is D * (X-V) = |X-V| * cos(@member m_angle). This equation is true if and
	// only if X point is on the cone surface.
	double a = pow(D.x * R.x, 2) + 2 * (D.x * R.x * D.y * R.y) + 2 * (D.x * R.x * D.z * R.z) + pow(D.y * R.y, 2)
			 + 2 * (D.y * R.y * D.z * R.z) + pow(D.z * R.z, 2) - pow(cos(m_angle), 2) * (pow(R.x, 2) + pow(R.y, 2) + pow(R.z, 2));
	double b = Vector3::dot(R, D) * (Vector3::dot(Ro, D) - Vector3::dot(V, D)) * 2
			 - 2 * pow(cos(m_angle), 2) * (R.x * (Ro.x - V.x) + R.y * (Ro.y - V.y) + R.z * (Ro.z - V.z));

	double c = pow(Vector3::dot(D, Ro) - Vector3::dot(V, D), 2) 
			 - pow(cos(m_angle), 2) * (pow(Ro.x - V.x, 2) + pow(Ro.y - V.y, 2) + pow(Ro.z - V.z, 2));

	float discriminant = pow(b, 2) - 4 * a * c;

	if (discriminant < -1e-5f) {
		// There is no solution satisfy this equation, no intersection.
		return false;
	}


	// t1 and t2 are coefficients for ray equation which is origin + direction * t
	float t1 = (-b - sqrt(abs(discriminant))) / (2 * a);
	float t2 = (-b + sqrt(abs(discriminant))) / (2 * a);

	float t;
	if (t1 < 0 && t2 < 0)
	{
		// Intersections are behind the camera. ignore the intersections.
		return false;
	}
	else if (t1 < 0)
	{
		// t1 is behind the camera. there is only one solution which is t2
		t = t2;
	}
	else if (t2 < 0)
	{
		// t2 is behind the camera. there is only one solution which is t1
		t = t1;
	}
	else
	{
		// Both solutions are in front of the camera. So take the closest one.
		if (t1 < t2) {
			t = t1;
		}
		else
		{
			t = t2;
		}
	}

	// Find the intersection point using ray's equation
	Vector3 hitPoint = ray.at(t);
	// Project the hit point onto the cone axis
	float hitHeight = Vector3::dot(hitPoint - V, D);

	if (hitHeight <= m_height && hitHeight >= 0) 
	{
		// Hit point is in the height range. 
		// Intersection
		return true;
	}

	// Hit point has farther distance than m_height.
	// No intersection
	return false;
}


Hit Cone::intersect(const Ray& ray) const
{
	/// Intersection check for the bottom disk ///
	Hit bottomHit = m_bottom.intersect(ray);

	if (bottomHit.isValid) {
		return bottomHit;
	}

	/// Intersection check for body of the cone ///
	Vector3 D = -m_direction; // Direction from top point to the center of bottom disk
	Vector3 V = m_topPoint;
	Vector3 R = ray.direction;
	Vector3 Ro = ray.origin;

	// Create a quadratic equation from the implicit equation of the cone and solve it.
	// The implicit equation is D * (X-V) = |X-V| * cos(@member m_angle). This equation is true if and
	// only if X point is on the cone surface.
	double a = pow(D.x * R.x, 2) + 2 * (D.x * R.x * D.y * R.y) + 2 * (D.x * R.x * D.z * R.z) + pow(D.y * R.y, 2)
		+ 2 * (D.y * R.y * D.z * R.z) + pow(D.z * R.z, 2) - pow(cos(m_angle), 2) * (pow(R.x, 2) + pow(R.y, 2) + pow(R.z, 2));
	double b = Vector3::dot(R, D) * (Vector3::dot(Ro, D) - Vector3::dot(V, D)) * 2
		- 2 * pow(cos(m_angle), 2) * (R.x * (Ro.x - V.x) + R.y * (Ro.y - V.y) + R.z * (Ro.z - V.z));

	double c = pow(Vector3::dot(D, Ro) - Vector3::dot(V, D), 2)
		- pow(cos(m_angle), 2) * (pow(Ro.x - V.x, 2) + pow(Ro.y - V.y, 2) + pow(Ro.z - V.z, 2));

	float discriminant = pow(b, 2) - 4 * a * c;

	if (discriminant < -1e-5f) {
		// There is no solution satisfy this equation, no intersection.
		return Hit();
	}


	// t1 and t2 are coefficients for ray equation which is origin + direction * t
	float t1 = (-b - sqrt(abs(discriminant))) / (2 * a);
	float t2 = (-b + sqrt(abs(discriminant))) / (2 * a);

	float t;
	if (t1 < 0 && t2 < 0)
	{
		// Intersections are behind the camera. ignore the intersections.
		return Hit();
	}
	else if (t1 < 0)
	{
		// t1 is behind the camera. there is only one solution which is t2
		t = t2;
	}
	else if (t2 < 0)
	{
		// t2 is behind the camera. there is only one solution which is t1
		t = t1;
	}
	else
	{
		// Both solutions are in front of the camera. So take the closest one.
		if (t1 < t2) {
			t = t1;
		}
		else
		{
			t = t2;
		}
	}

	// Find the intersection point using ray's equation
	Vector3 hitPoint = ray.at(t);
	// Projecting hit point onto the cone axis
	float hitHeight = Vector3::dot(hitPoint - V, D);

	if (hitHeight <= m_height && hitHeight >= 0)
	{
		// Hit point is in the height range. There is no condition left.
		// Prepare the hit informations and return them.

		// Find the unit vector perpendicular to (hitPoint-V) and also intersecting with the cone axis. 
		Vector3 normal = (hitPoint - (V + D * (hitPoint - V).length()/cos(m_angle))).unit_vector();
		// Distance between hitPoint and ray origin point.
		float bodyHitDistance = (hitPoint - ray.origin).length();

		// Return hit informations
		return Hit{
			true,
			hitPoint,
			normal,
			m_material,
			bodyHitDistance
		};
	}

	// Hit point has farther distance than m_height.
	// No intersection
	return Hit();

}