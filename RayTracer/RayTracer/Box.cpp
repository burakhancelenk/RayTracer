#include "Box.h"
#include "Vector3.h"
#include "Ray.h"
#include "math.h"
#include <limits>

using namespace Primitive;

Box::Box()
	: m_center(0,0,0)
	, m_upVector(0,0,1)
	, m_frontVector(0,1,0)
	, m_width(0.2)
	, m_height(0.2)
	, m_depth(0.2)
	, m_material()
{
	m_surfaces.resize(6);

	// Filling informations about box surfaces
	m_surfaces[0] = Plane(
		m_center + m_upVector * m_height/2.0f,
		m_upVector,
		m_frontVector,
		m_depth,
		m_width,
		false,
		m_material
	);
	m_surfaces[1] = Plane(
		m_center + m_frontVector * m_width/2.0f,
		m_frontVector,
		m_upVector,
		m_depth,
		m_height,
		false,
		m_material
	);
	m_surfaces[2] = Plane(
		m_center - m_upVector * m_height/2.0f,
		-m_upVector,
		m_frontVector,
		m_depth,
		m_width,
		false,
		m_material
	);
	m_surfaces[3] = Plane(
		m_center - m_frontVector * m_width/2.0f,
		-m_frontVector,
		m_upVector,
		m_depth,
		m_height,
		false,
		m_material
	);
	m_surfaces[4] = Plane(
		m_center - Vector3::cross(m_frontVector, m_upVector) * m_depth/2.0f,
		-Vector3::cross(m_frontVector, m_upVector).unit_vector(),
		m_upVector,
		m_width,
		m_height,
		false,
		m_material
	);
	m_surfaces[5] = Plane(
		m_center + Vector3::cross(m_frontVector, m_upVector) * m_depth/2.0f,
		Vector3::cross(m_frontVector, m_upVector).unit_vector(),
		m_upVector,
		m_width,
		m_height,
		false,
		m_material
	);
}

Box::Box(
	const Vector3& center,
	const Vector3& upVector,
	const Vector3& frontVector,
	float width,
	float height,
	float depth
)
	: m_center(center)
	, m_upVector(upVector.unit_vector())
	, m_frontVector(frontVector.unit_vector())
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_material()
{

	m_surfaces.resize(6);

	// Filling informations about box surfaces
	m_surfaces[0] = Plane(
		m_center + m_upVector * m_height/2.0f,
		m_upVector,
		m_frontVector,
		m_depth,
		m_width,
		false,
		m_material
	);
	m_surfaces[1] = Plane(
		m_center + m_frontVector * m_width/2.0f,
		m_frontVector,
		m_upVector,
		m_depth,
		m_height,
		false,
		m_material
	);
	m_surfaces[2] = Plane(
		m_center - m_upVector * m_height/2.0f,
		-m_upVector,
		m_frontVector,
		m_depth,
		m_width,
		false,
		m_material
	);
	m_surfaces[3] = Plane(
		m_center - m_frontVector * m_width/2.0f,
		-m_frontVector,
		m_upVector,
		m_depth,
		m_height,
		false,
		m_material
	);
	m_surfaces[4] = Plane(
		m_center - Vector3::cross(m_frontVector, m_upVector) * m_depth/2.0f,
		-Vector3::cross(m_frontVector, m_upVector).unit_vector(),
		m_upVector,
		m_width,
		m_height,
		false,
		m_material
	);
	m_surfaces[5] = Plane(
		m_center + Vector3::cross(m_frontVector, m_upVector) * m_depth/2.0f,
		Vector3::cross(m_frontVector, m_upVector).unit_vector(),
		m_upVector,
		m_width,
		m_height,
		false,
		m_material
	);

}

Box::Box(
	const Vector3& center,
	const Vector3& upVector,
	const Vector3& frontVector,
	float width,
	float height,
	float depth,
	const Material& material
) 
	: m_center(center)
	, m_upVector(upVector.unit_vector())
	, m_frontVector(frontVector.unit_vector())
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_material(material)
{

	m_surfaces.resize(6);

	// Filling informations about box surfaces
	m_surfaces[0] = Plane(
		m_center + m_upVector * m_height/2.0f,
		m_upVector,
		m_frontVector,
		m_depth,
		m_width,
		false,
		m_material
	);
	m_surfaces[1] = Plane(
		m_center + m_frontVector * m_width/2.0f,
		m_frontVector,
		m_upVector,
		m_depth,
		m_height,
		false,
		m_material
	);
	m_surfaces[2] = Plane(
		m_center - m_upVector * m_height/2.0f,
		-m_upVector,
		m_frontVector,
		m_depth,
		m_width,
		false,
		m_material
	);
	m_surfaces[3] = Plane(
		m_center - m_frontVector * m_width/2.0f,
		-m_frontVector,
		m_upVector,
		m_depth,
		m_height,
		false,
		m_material
	);
	m_surfaces[4] = Plane(
		m_center - Vector3::cross(m_frontVector, m_upVector) * m_depth/2.0f,
		-Vector3::cross(m_frontVector, m_upVector).unit_vector(),
		m_upVector,
		m_width,
		m_height,
		false,
		m_material
	);
	m_surfaces[5] = Plane(
		m_center + Vector3::cross(m_frontVector, m_upVector) * m_depth/2.0f,
		Vector3::cross(m_frontVector, m_upVector).unit_vector(),
		m_upVector,
		m_width,
		m_height,
		false,
		m_material
	);

}

bool Box::intersect_first_image(const Ray& ray) const {
	// There is only 3 surfaces could intersect with the ray. And these are
	// the closest 3 surfaces. For gain a little bit performance, we will determine
	// these 3 surfaces and make intersection test onyl for them.

	// Calculate the distances between surface centers and ray origin
	float distances[6];
	for (int i = 0; i < m_surfaces.size(); i++)
	{
		distances[i] = (m_surfaces[i].center() - ray.origin).length_squared();
	}

	// Determine the closest 3 surfaces
	int closestSurfaces[3];
	for (int i = 0; i < 3; i++)
	{
		int temp = 0;
		for (int i = 0; i < 6; i++) 
		{
			if (distances[temp] > distances[i]) {
				temp = i;
			}
		}
		distances[temp] = std::numeric_limits<float>::infinity();
		closestSurfaces[i] = temp;
	}

	// Make an intersection test for these surfaces
	bool isHit1 = m_surfaces[closestSurfaces[0]].intersect_first_image(ray);
	bool isHit2 = m_surfaces[closestSurfaces[1]].intersect_first_image(ray);
	bool isHit3 = m_surfaces[closestSurfaces[2]].intersect_first_image(ray);

	if (isHit1 || isHit2 || isHit3) {
		// At least one of them must have an intersection
		return true;
	}

	// Otherwise no intersection
	return false;
}

Hit Box::intersect(const Ray& ray) const {
	// There is only 3 surfaces could intersect with the ray. And these are
	// the closest 3 surfaces. For gain a little bit performance, we will determine
	// these 3 surfaces and make intersection test onyl for them.

	// Calculate the distances between surface centers and ray origin
	float distances[6];
	for (int i = 0; i < m_surfaces.size(); i++)
	{
		distances[i] = (m_surfaces[i].center() - ray.origin).length_squared();
	}

	// Determine the closest 3 surfaces
	int closestSurfaces[3];
	for (int i = 0; i < 3; i++)
	{
		int temp = 0;
		for (int i = 0; i < 6; i++)
		{
			if (distances[temp] > distances[i]) {
				temp = i;
			}
		}
		distances[temp] = std::numeric_limits<float>::infinity();
		closestSurfaces[i] = temp;
	}

	// Make an intersection test for these surfaces
	Hit Hit1 = m_surfaces[closestSurfaces[0]].intersect(ray);
	Hit Hit2 = m_surfaces[closestSurfaces[1]].intersect(ray);
	Hit Hit3 = m_surfaces[closestSurfaces[2]].intersect(ray);

	// At least one of them must have an intersection
	if (Hit1.isValid) return Hit1;
	if (Hit2.isValid) return Hit2;
	if (Hit3.isValid) return Hit3;

	// Otherwise no intersection
	return Hit();
}