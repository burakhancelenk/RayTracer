#include "SpotLight.h"

#define PI 3.14159265

using namespace Core;

SpotLight::SpotLight()
	: m_minIntensity(0)
	, m_maxIntensity(2)
	, m_innerRadius(1)
	, m_outerRadius(3)
	, m_maxDistance(15)
	, m_position(0, 0, 0)
	, m_direction(1, 0, 0)
	, m_color(1, 1, 1)
	, m_radius(0.2)
{}

SpotLight::SpotLight(
	const Vector3& position,		
	const Vector3& direction,
	const Vector3& color)

	: m_minIntensity(0)
	, m_maxIntensity(2)
	, m_innerRadius(1)
	, m_outerRadius(3)
	, m_maxDistance(15)
	, m_radius(0.2)
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
	float maxDistance,
	float radius)

	: m_minIntensity(minIntensity)
	, m_maxIntensity(maxDistance)
	, m_innerRadius(innerRadius)
	, m_outerRadius(outerRadius)
	, m_maxDistance(maxDistance)
	, m_radius(radius)
	, m_position(position)
	, m_direction(direction)
	, m_color(color)
{}

void SpotLight::at(
	bool realLightBehaviour,
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const
{
	Vector3 v = m_position - position;
	distance = v.length();
	direction = v / distance;

	
	// Find perpendicular unit vector to m_direction
	Vector3 pV = Vector3(-m_direction.z, 0, -m_direction.x).unit_vector();

	// Find the edge of the spot light according to the direction.
	Vector3 edgeVector = (m_direction + pV * m_outerRadius / m_maxDistance)
							.unit_vector();

	// Find the dot products of (m_direction , edgeVector) and (m_direction , -v)
	float d1 = Vector3::dot(m_direction, edgeVector);
	float d2 = Vector3::dot(m_direction, -v.unit_vector());

	if (d1 > d2 || (distance > m_maxDistance && !realLightBehaviour)) {
		//The point is out of range
		intensity = Vector3(0, 0, 0);
		return;
	}

	// Find the edge vector of the inner cone
	Vector3 innerEdgeVector = (m_direction + pV * m_innerRadius / m_maxDistance)
								.unit_vector();
	float d3 = Vector3::dot(m_direction, innerEdgeVector);

	float minIntensity = realLightBehaviour ? 0 : m_minIntensity;
	float interpolatedInts;

	if (d2 >= d3)
	{
		// The point is in the inner cone
		interpolatedInts = m_maxIntensity;
	}
	else
	{
		// The point is in the outer cone, calculate the interpolated intensity
		interpolatedInts = m_minIntensity + (m_maxIntensity - m_minIntensity) * (abs(d2 - d1) / abs(d1 - d3));
	}

	if (realLightBehaviour) {
		intensity = m_color * interpolatedInts / pow(distance, 2);
	}
	else
	{
		intensity = m_color * interpolatedInts * (pow(m_maxDistance - distance, 2) / pow(m_maxDistance, 2));
	}
}

// override Light::get_sample_points
void SpotLight::get_sample_points(
	const Vector3& hitPoint,
	std::vector<Vector3>& samplePoints,
	int sampleAmount) const
{

	// Rotation axis
	Vector3 rotAxis = m_direction;

	// The vector that we will rotate
	Vector3 rotAxisNormal = Vector3(-rotAxis.z, 0, -rotAxis.x).unit_vector();

	// first sample point is light position
	samplePoints.push_back(m_position);

	// For each degree we take @param sampleAmount sample points and we divided 360 degree to 2 * sampleAmount
	// at total 2 * sampleAmount * sampleAmount + 1 sample points
	for (int i = 1; i <= 2 * sampleAmount; i++)
	{
		for (int j = 1; j <= sampleAmount; j++) {
			samplePoints.push_back(rotAxisNormal * m_radius * j / float(sampleAmount) + m_position);
		}
		rotAxisNormal = Vector3::rotate(rotAxisNormal, rotAxis, PI / float(sampleAmount));
	}

}