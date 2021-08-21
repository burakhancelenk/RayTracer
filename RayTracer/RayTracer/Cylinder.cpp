#include "Cylinder.h"

using namespace Primitive;

Cylinder::Cylinder()
	: m_center(0, 0, 0)
	, m_direction(0,0,1)
	, m_radius(0.5)
	, m_height(2)
	, m_material()
{
	// Prepare the top and bottom disks according to the given informations
	m_top = Disk(m_center + m_direction * m_height / 2.0f,
				 m_direction,
				 m_radius,
				 false,
				 m_material);

	m_bottom = Disk(m_center - m_direction * m_height / 2.0f,
					-m_direction,
					m_radius,
					false,
					m_material);

}

Cylinder::Cylinder(
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

	// Prepare the top and bottom disks according to the given informations
	m_top = Disk(m_center + m_direction * m_height / 2.0f,
				 m_direction,
				 m_radius,
				 false,
				 m_material);

	m_bottom = Disk(m_center - m_direction * m_height / 2.0f,
					-m_direction,
					m_radius,
					false,
					m_material);

}

Cylinder::Cylinder(
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

	// Prepare the top and bottom disks according to the given informations
	m_top = Disk(m_center + m_direction * m_height / 2.0f,
				 m_direction,
				 m_radius,
				 false,
				 m_material);

	m_bottom = Disk(m_center - m_direction * m_height / 2.0f,
					-m_direction,
					m_radius,
					false,
					m_material);

}

bool Cylinder::intersect_first_image(const Ray& ray) const
{
	/// Intersection check for top and bottom disks ///
	Hit topHit = m_top.intersect(ray);
	Hit bottomHit = m_bottom.intersect(ray);

	if (topHit.isValid || bottomHit.isValid) {
		return true;
	}

	/// Intersection check for body of the cylinder ///

	// First of all we will create a local coordinate system whose center
	// is a point on the Cylinder's direction axis
	Vector3 xAxis = Vector3::cross(ray.direction, m_direction).unit_vector();
	Vector3 zAxis = m_direction;
	Vector3 yAxis = Vector3::cross(zAxis, xAxis).unit_vector();

	// Smallest line segment which is projection of the ray to the x axis
	Vector3 segment = xAxis * Vector3::dot(ray.origin - m_center + m_direction * m_height / 2.0f, xAxis);

	if (segment.length_squared() > pow(m_radius, 2)) {
		// The closest point on the ray has a farther distance than radius to the cylinder axis. 
		// So there is no intersection
		return false;
	}

	// Create a quadratic equation from the implicit equation of the cylinder and solve it.
	// The implicit equation is (x2 + y2 = r2). To solve this equation correctly we need to apply it
	// in local coordinate system whose z axis is equal to the cylinder's direction axis.

	Vector3 Or_center = ray.origin - m_center;

	double a = pow(Vector3::dot(ray.direction, xAxis), 2) + pow(Vector3::dot(ray.direction, yAxis), 2);

	double b = Vector3::dot(ray.direction, xAxis) * Vector3::dot(Or_center, xAxis) * 2
			 + Vector3::dot(ray.direction, yAxis) * Vector3::dot(Or_center, yAxis) * 2;

	double c = pow(Or_center.x * xAxis.x, 2) + pow(Or_center.y * xAxis.y, 2) + pow(Or_center.z * xAxis.z, 2)
			 + pow(Or_center.x * yAxis.x, 2) + pow(Or_center.y * yAxis.y, 2) + pow(Or_center.z * yAxis.z, 2)
			 + 2 * (Or_center.x * xAxis.x * Or_center.y * xAxis.y +
					Or_center.x * xAxis.x * Or_center.z * xAxis.z +
					Or_center.y * xAxis.y * Or_center.z * xAxis.z)
			 + 2 * (Or_center.x * yAxis.x * Or_center.y * yAxis.y +
					Or_center.x * yAxis.x * Or_center.z * yAxis.z +
					Or_center.y * yAxis.y * Or_center.z * yAxis.z)
			 - pow(m_radius, 2); 

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
	// Project the hit point onto the cylinder axis
	float hitHeight = abs(Vector3::dot(hitPoint - m_center, zAxis));

	if (hitHeight <= m_height / 2.0f) {
		// Hit point is in the height range. 
		// Intersection
		return true;
	}

	// Hit point has farther distance than m_height.
	// No intersection
	return false;
}

Hit Cylinder::intersect(const Ray& ray) const
{
	/// Intersection check for top and bottom disks ///
	Hit topHit = m_top.intersect(ray);
	Hit bottomHit = m_bottom.intersect(ray);

	/// Intersection check for body of the cylinder ///

	// First of all we will create a local coordinate system whose center
	// is a point on the on the Cylinder's direction axis
	Vector3 xAxis = Vector3::cross(ray.direction, m_direction).unit_vector();
	Vector3 zAxis = m_direction;
	Vector3 yAxis = Vector3::cross(zAxis, xAxis).unit_vector();

	// Smallest line segment which is projection of the ray to the x axis
	Vector3 segment = xAxis * Vector3::dot(ray.origin - m_center + m_direction * m_height / 2.0f, xAxis);

	if (segment.length_squared() > pow(m_radius, 2)) {
		// The closest point on the ray has a farther distance than radius to the cylinder axis. 
		// So there is no intersection
		return Hit();
	}

	// Create a quadratic equation from the implicit equation of the cylinder and solve it.
	// The implicit equation is (x2 + y2 = r2). To solve this equation correctly we need to apply it
	// in local coordinate system whose z axis is equal to the cylinder axis.

	Vector3 Or_center = ray.origin - m_center;

	double a = pow(Vector3::dot(ray.direction, xAxis), 2) + pow(Vector3::dot(ray.direction, yAxis), 2);

	double b = Vector3::dot(ray.direction, xAxis) * Vector3::dot(Or_center, xAxis) * 2
			 + Vector3::dot(ray.direction, yAxis) * Vector3::dot(Or_center, yAxis) * 2;

	double c = pow(Or_center.x * xAxis.x, 2) + pow(Or_center.y * xAxis.y, 2) + pow(Or_center.z * xAxis.z, 2)
			 + pow(Or_center.x * yAxis.x, 2) + pow(Or_center.y * yAxis.y, 2) + pow(Or_center.z * yAxis.z, 2)
			 + 2 * (Or_center.x * xAxis.x * Or_center.y * xAxis.y +
					Or_center.x * xAxis.x * Or_center.z * xAxis.z +
					Or_center.y * xAxis.y * Or_center.z * xAxis.z)
			 + 2 * (Or_center.x * yAxis.x * Or_center.y * yAxis.y +
					Or_center.x * yAxis.x * Or_center.z * yAxis.z +
					Or_center.y * yAxis.y * Or_center.z * yAxis.z)
			 - pow(m_radius, 2);

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

	if (abs(Vector3::dot(hitPoint - m_center, zAxis)) > m_height / 2.0f) {
		// Hit point is out of height range. 
		// Check disk intersections. If there is an intersection, return it.
		if (topHit.isValid)
		{
			return topHit;
		}
		else if (bottomHit.isValid)
		{
			return bottomHit;
		}

		// There is no intersection for disks. We have already eliminated body intersection
		// because of "out of height range". No intersection.
		return Hit();
	}

	
	// If we are in here, then the hit point is in the height range and also in the radius range.
	// So prepare the hit informations and return them.

	// Find the center point(on the zAxis) of the circle which has equal z value with the intersection point
	Vector3 hitCenter = zAxis * Vector3::dot(hitPoint - m_center, zAxis) + m_center;
	// Find the normal vector of the intersection point
	Vector3 normal = (hitPoint - hitCenter).unit_vector();
	// Find the distance between the hit point and ray origin point
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