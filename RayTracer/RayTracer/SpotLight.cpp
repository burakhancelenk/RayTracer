#include "SpotLight.h"

using namespace Core;

SpotLight::SpotLight()
	: m_minIntensity(1)
	, m_maxIntensity(2)
	, m_innerRadius(1)
	, m_outerRadius(3)
	, m_maxDistance(15)
	, m_position(0,0,0)
	, m_direction(1,0,0)
	, m_color(1,1,1)
{}

SpotLight::SpotLight(
	const Vector3& position,		
	const Vector3& direction,
	const Vector3& color)

	: m_minIntensity(1)
	, m_maxIntensity(2)
	, m_innerRadius(1)
	, m_outerRadius(3)
	, m_maxDistance(15)
	, m_position(position)
	, m_direction(direction)
	, m_color(color)
{}

SpotLight::SpotLight(
	const Vector3& position,
	const Vector3& direction,
	const Vector3& color,
	float minIntensity,
	float maxIntensity,
	float innerRadius,
	float outerRadius,
	float maxDistance)

	: m_minIntensity(minIntensity)
	, m_maxIntensity(maxDistance)
	, m_innerRadius(innerRadius)
	, m_outerRadius(outerRadius)
	, m_maxDistance(maxDistance)
	, m_position(position)
	, m_direction(direction)
	, m_color(color)
{}

void SpotLight::at(
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const
{
	Vector3 v = m_position - position;
	distance = v.length();
	direction = v / distance;

	/* Find the perpendicular unit vector to m_direction
	*	1 - Dot product must be zero because they are perpendicular to each other
	*	2 - There are 3 unknown (x,y,z)
	*	3 - Give an arbitrary value to x and y
	*	4 - Calculate dot product, set it equal to zero and find the z value
	 */
	float x, y, z;
	// m_direction.x + m_direction.y + m_direction.z * z = 0
	if (m_direction.z <= 1e-6 && m_direction.z > -1e-6) {
		x = 0;
		y = 0;
		z = 1;
	}
	else
	{
		x = 1;
		y = 1;
		z = (-m_direction.x - m_direction.y) / m_direction.z;
	}
	
	// Perpendicular unit vector
	Vector3 pV = Vector3(x,y,z).unit_vector();

	// Find the edge of the spot light according to the direction.
	Vector3 edgeVector = (m_direction + pV * m_outerRadius / m_maxDistance)
							.unit_vector();

	// Find the dot products of (m_direction , edgeVector) and (m_direction , -v)
	float d1 = Vector3::dot(m_direction, edgeVector);
	float d2 = Vector3::dot(m_direction, -v.unit_vector());

	if (d1 > d2 || distance > m_maxDistance) {
		//The point is out of range
		intensity = Vector3(0, 0, 0);
		return;
	}

	// Find the edge vector of the inner cone
	Vector3 innerEdgeVector = (m_direction + pV * m_innerRadius / m_maxDistance)
								.unit_vector();
	float d3 = Vector3::dot(m_direction, innerEdgeVector);
	if (d2 >= d3)
	{
		// The point is in the inner cone
		intensity = m_color * m_maxIntensity / distance;
		//std::cout << "Intensity value :" << intensity << " \n";
	}
	else
	{
		// The point is in the outer cone
		// Calculate the interpolated intensity and update @param intensity
		float interpolatedInts = m_minIntensity + (m_maxIntensity - m_minIntensity)
								* (abs(d2-d1)/abs(d1-d3));
		intensity = m_color * interpolatedInts / distance;
	}
}